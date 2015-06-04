//
// Created by german on 03.06.15.
//

#include "RequestUtils.h"

std::vector<std::string> RequestUtils::splitStringBySpace(const std::string &s) {
    std::vector<std::string> result;
    result.push_back("");
    for (char c : s) {
        if (isspace(c)) {
            if (result.back().size() > 0) {
                result.push_back("");
            }
        } else {
            result.back() += c;
        }
    }
    if (result.back().size() == 0) {
        result.pop_back();
    }
}

bool RequestUtils::isGetRequest(const std::string &s) {
    int i = 0;
    while (i < s.length() && isspace(s[i])) i++;
    return i + 2 < s.length() && s[i] == 'G' && s[i + 1] == 'E' && s[i + 2] == 'T';
}

std::vector<std::string> RequestUtils::requestMethods;
std::vector<std::string> RequestUtils::generalHeaders;
std::vector<std::string> RequestUtils::requestHeaders;

std::vector<std::string> &RequestUtils::getRequestMethods() {
    if (requestMethods.size() == 0) {
        requestMethods.push_back("GET");
        requestMethods.push_back("POST");
    }
    return requestMethods;
}

std::vector<std::string> &RequestUtils::getGeneralHeaders() {
    if (generalHeaders.size() == 0) {
        generalHeaders.push_back("Cache-Control");
        generalHeaders.push_back("Connection");
        generalHeaders.push_back("Date");
    }
    return generalHeaders;
}

std::vector<std::string> &RequestUtils::getRequestHeaders() {
    if (requestHeaders.size() == 0) {
        requestHeaders.push_back("Accept-Encoding");
        requestHeaders.push_back("Accept-Language");
        requestHeaders.push_back("Accept");         // should be after Accept*
        requestHeaders.push_back("Host");
        requestHeaders.push_back("User-Agent");
    }
    return requestHeaders;
}

void RequestUtils::addMapValuesToString(const std::map<std::string, std::string> &mp, std::string &s) {
    for (auto &it : mp) {
        s += it.first + ": " + it.second + "\r\n";
    }
}

std::string RequestUtils::getIntAsString(int x) {
    std::string res = "";
    do {
        res += x % 10 + '0';
        x /= 10;
    } while (x);
    for (int i = 0; i < res.length() / 2; i++) {
        std::swap(res[i], res[res.length() - i - 1]);
    }
    return res;
}
