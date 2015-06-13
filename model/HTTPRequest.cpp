//
// Created by german on 04.06.15.
//

#include <iostream>
#include "HTTPRequest.h"
#include "../HTTPServer/RequestUtils.h"
#include "HTTPException.h"


bool HTTPRequest::checkFullRequest(const std::string &s, int &from, std::string extraMessage = "") {
    if (s.length() <= from) throw NotFullRequestException("Not Full Request" + (extraMessage.length() != 0 ? " (" + extraMessage + ")" : ""));
    return true;
}

void HTTPRequest::checkSP(const std::string &s, int &from, std::string extraMessage = "") {
    checkFullRequest(s, from, extraMessage);
    if (s[from] != ' ') {
        throw HTTPException("SP expected" + (extraMessage.length() != 0 ? " (" + extraMessage + ")" : ""));
    }
    from++;
}

void HTTPRequest::checkCRLF(const std::string &s, int &from, std::string extraMessage = "") {
    checkFullRequest(s, from, extraMessage);
    if (s[from] == '\r') {
        from++;
    }
    checkFullRequest(s, from, extraMessage);
    if (s[from] != '\n') {
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
    checkSP(s, from, "Request Line, sp after method");

    while (!isspace(s[from])) {
        requestUri += s[from];
        from++;
    }

    checkSP(s, from, "Request Line, sp after uri");

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
                      std::map<std::string, std::string> &headersMap,
                      std::vector<std::string> availableHeaders,
                      std::string headerType) {
    for (std::string &header : availableHeaders) {
        if (s.substr(from, header.size()) == header) {
            from += header.size();
            checkFullRequest(s, from);
            if (s[from] != ':') {
                throw HTTPException(" \':\' after " + headerType + " " + header + " expected");
            }
            from++;
            checkFullRequest(s, from);
            if (s[from] != ' ') {
                throw HTTPException(" \' \' after " + headerType + " " + header + " expected");
            }
            from++;
            std::string value;
            while (from < s.length()) {
                if (s[from] == '\n' || from + 1 < s.length() && s[from] == '\r' && s[from + 1] == '\n') break;
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


bool HTTPRequest::parseExtraHeader(const std::string &s, int &from) {
    int oldFrom = from;
    std::string key = "";
    while (from < s.length() && !isspace(s[from]) && s[from] != ':') {
        key += s[from];
        from++;
    }
    if (from == oldFrom) {
        return false;
    }
    checkFullRequest(s, from);
    if (s[from] != ':') {
        throw HTTPException(" \':\' after extra header " + key + " expected");
    }
    from++;
    checkFullRequest(s, from);
    if (s[from] != ' ') {
        throw HTTPException(" \' \' after extra header " + key + " expected");
    }
    from++;
    std::string value;
    while (from < s.length()) {
        if (s[from] == '\n' || from + 1 < s.length() && s[from] == '\r' && s[from + 1] == '\n') break;
        value += s[from];
        from++;
    }
    checkCRLF(s, from, "extra header " + key);
    extraHeaders[key] = value;
    return true;
}

HTTPRequest::HTTPRequest(const std::string &s) {
    int pos = 0;
    parseRequestLine(s, pos);

    while (pos < s.length() && (parseRequestHeader(s, pos) || parseGeneralHeader(s, pos) || parseExtraHeader(s, pos)));
    checkCRLF(s, pos, "end of request before message_body");
    messageBody = s.substr(pos);
}

const std::string &HTTPRequest::getMethod() const {
    return method;
}

HTTPRequest::HTTPRequest() {
}

const std::string &HTTPRequest::getMessageBody() const {
    return messageBody;
}

const std::string &HTTPRequest::getRequestUri() const {
    return requestUri;
}
