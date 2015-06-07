//
// Created by german on 04.06.15.
//

#include "HTTPResponse.h"
#include "HTTPException.h"
#include "../HTTPServer/RequestUtils.h"

void HTTPResponse::setHttpVersion(const std::string &httpVersion) {
    if (httpVersion.substr(0, 5) != "HTTP/") {
        throw HTTPException("HTTP version incorrect format");
    }
    if (!isdigit(httpVersion[5]) || httpVersion[6] != '.' || !isdigit(httpVersion[7])) {
        throw HTTPException("HTTP version incorrect format");
    }
    this->httpVersion = httpVersion;
}

void HTTPResponse::setStatusCode(const int statusCode) {
    if (statusCode > 999) {
        throw new HTTPException("Status code must be consist of 3 digits");
    }
    this->statusCode = statusCode;
}

void HTTPResponse::setReasonPhrase(const std::string &reasonPhrase) {
    for (char c : reasonPhrase) {
        if (c == '\r' || c == '\n') {
            throw HTTPException("Bad reason phrase, it must be without CR and LF");
        }
    }
    this->reasonPhrase = reasonPhrase;
}

void HTTPResponse::addGeneralHeader(const std::string &generalHeader, const std::string &value) {
    generalHeaders[generalHeader] = value;
}

void HTTPResponse::addResponseHeader(const std::string &responseHeader, const std::string &value) {
    responseHeaders[responseHeader] = value;
}

void HTTPResponse::addEntityHeader(const std::string &entityHeader, const std::string &value) {
    entityHeaders[entityHeader] = value;
}

std::string HTTPResponse::buildResponse() {
    std::string res;
    res += httpVersion;
    res += ' ';

    res += RequestUtils::getIntAsString(statusCode);
    res += ' ';

    res += reasonPhrase;
    res += "\r\n";

    entityHeaders["Content-Length"] = RequestUtils::getIntAsString(messageBody.length());
    if (entityHeaders.find("Content-Type") == entityHeaders.end() || entityHeaders["Content-Type"].length() == 0) {
        entityHeaders["Content-Type"] = "text/plain";
    }

    RequestUtils::addMapValuesToString(generalHeaders, res);
    RequestUtils::addMapValuesToString(responseHeaders, res);
    RequestUtils::addMapValuesToString(entityHeaders, res);

    res += "\r\n";

    res += messageBody;

    return res;
}


void HTTPResponse::setMessageBody(const std::string &messageBody) {
    this->messageBody = messageBody;
}
