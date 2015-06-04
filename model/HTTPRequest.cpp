//
// Created by german on 04.06.15.
//

#include <iostream>
#include "HTTPRequest.h"
#include "../HTTPServer/RequestUtils.h"
#include "HTTPException.h"

void HTTPRequest::checkSP(const std::string &s, int &from, std::string extraMessage = "") {
    if (from >= s.length() || s[from] != ' ') {
        throw HTTPException("SP expected" + (extraMessage.length() != 0 ? " (" + extraMessage + ")" : ""));
    }
    from++;
}

void HTTPRequest::checkCRLF(const std::string &s, int &from, std::string extraMessage = "") {
    if (from >= s.length() || s[from] != '\r') {
        throw HTTPException("CR expected" + (extraMessage.length() != 0 ? " (" + extraMessage + ")" : ""));
    }
    from++;
    if (from >= s.length() || s[from] != '\n') {
        throw HTTPException("LF expected" + (extraMessage.length() != 0 ? " (" + extraMessage + ")" : ""));
    }
    from++;
}

void HTTPRequest::parseRequestLine(const std::string &s, int &from) {
    bool found = false;
    for (std::string &method : RequestUtils::getRequestMethods()) {
        if (s.substr(from, method.size()) == method) {
            this->method = method;
            found = true;
            break;
        }
    }
    if (!found) {
        throw HTTPException("Incorrect request method");
    }
    from += method.size();

    checkSP(s, from, "Request Line");

    while (!isspace(s[from])) {
        requestUri += s[from];
        from++;
    }

    checkSP(s, from, "Request Line");

    if (s.substr(from, 5) != "HTTP/") {
        throw HTTPException("HTTP version expected");
    }
    from += 5;
    if (!isdigit(s[from]) || s[from + 1] != '.' || !isdigit(s[from + 2])) {
        throw HTTPException("HTTP version expected");
    }
    from += 3;
    httpVersion = s.substr(from - 8, 8);

    checkCRLF(s, from, "Request Line");
}

bool HTTPRequest::parseHeaderInMap(const std::string &s, int &from,
                      std::map<std::string, std::string> headersMap,
                      std::vector<std::string> availableHeaders,
                      std::string headerType) {
    for (std::string &header : availableHeaders) {
        if (s.substr(from, header.size()) == header) {
            from += header.size();
            if (from >= s.length() || s[from] != ':') {
                throw HTTPException(" \':\' after " + headerType + " " + header + " expected");
            }
            from++;
            if (from >= s.length() || s[from] != ' ') {
                throw HTTPException(" \' \' after " + headerType + " " + header + " expected");
            }
            from++;
            std::string value;
            while (from + 1 < s.length() && s.substr(from, 2) != "\r\n") {
                value += s[from];
                from++;
            }
            checkCRLF(s, from, headerType + " " + header);
            headersMap[header] = value;
            return true;
        }
    }
    return false;
}

bool HTTPRequest::parseGeneralHeader(const std::string &s, int &from) {
    return parseHeaderInMap(s, from, generalHeaders, RequestUtils::getGeneralHeaders(), "general header");
}

bool HTTPRequest::parseRequestHeader(const std::string &s, int &from) {
    return parseHeaderInMap(s, from, requestHeaders, RequestUtils::getRequestHeaders(), "request header");
}

HTTPRequest::HTTPRequest(const std::string &s) {
    int pos = 0;
    parseRequestLine(s, pos);
    while (pos < s.length() && (parseRequestHeader(s, pos) || parseGeneralHeader(s, pos)));
    checkCRLF(s, pos, "end of request before message_body");
    messageBody = s.substr(pos);
}

const std::string &HTTPRequest::getMethod() const {
    return method;
}

HTTPRequest::HTTPRequest() {
}
