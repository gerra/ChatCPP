//
// Created by german on 04.06.15.
//

#ifndef CHATCPP_HTTPREQUEST_H
#define CHATCPP_HTTPREQUEST_H

#include <string>
#include <map>
#include <vector>

class HTTPRequest {
    std::string method;
    std::string requestUri;
    std::string httpVersion;

    std::map<std::string, std::string> generalHeaders;
    std::map<std::string, std::string> requestHeaders;
    std::map<std::string, std::string> extraHeaders;

    std::string messageBody;

    void checkSP(const std::string &s, int &from, std::string extraMessage);
    void checkCRLF(const std::string &s, int &from, std::string extraMessage);

    void parseRequestLine(const std::string &s, int &from);

    bool parseHeaderInMap(const std::string &s, int &from,
                          std::map<std::string, std::string> headersMap,
                          std::vector<std::string> availableHeaders,
                          std::string headerType);
    bool parseGeneralHeader(const std::string &s, int &from);
    bool parseRequestHeader(const std::string &s, int &from);
    bool parseExtraHeader(const std::string &s, int &from);
public:
    HTTPRequest(const std::string &s);

    const std::string &getMethod() const;
    const std::string &getMessageBody() const;
    const std::string &getRequestUri() const;

    HTTPRequest();
};


#endif //CHATCPP_HTTPREQUEST_H
