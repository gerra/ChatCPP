//
// Created by german on 04.06.15.
//

#ifndef CHATCPP_HTTPRESPONSE_H
#define CHATCPP_HTTPRESPONSE_H

#include <string>
#include <map>

class HTTPResponse {

    std::string httpVersion;
    int statusCode;
    std::string reasonPhrase;
    std::string messageBody;

    std::map<std::string, std::string> generalHeaders;
    std::map<std::string, std::string> responseHeaders;
    std::map<std::string, std::string> entityHeaders;

public:
    void setHttpVersion(const std::string &httpVersion);
    void setStatusCode(const int statusCode);
    void setReasonPhrase(const std::string &reasonPhrase);
    void addGeneralHeader(const std::string &generalHeader, const std::string &value);
    void addResponseHeader(const std::string &responseHeader, const std::string &value);
    void addEntityHeader(const std::string &entityHeader, const std::string &value);
    void setMessageBody(const std::string &messageBody);
    std::string buildResponse();
};



#endif //CHATCPP_HTTPRESPONSE_H
