//
// Created by german on 03.06.15.
//

#include <fstream>
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

std::string RequestUtils::getValueFromJsonByKey(const std::string &jsonStr, const std::string &key) {
    for (int i = 0; i < jsonStr.length(); i++) {
        if (jsonStr.substr(i, key.length()) == key) {
            int pos = i + key.length();
            while (pos < jsonStr.length() && jsonStr[pos] == ' ') pos++;
            if (jsonStr[pos++] != '\"') return "";
            while (pos < jsonStr.length() && jsonStr[pos] == ' ') pos++;
            if (jsonStr[pos++] != ':') return "";
            while (pos < jsonStr.length() && jsonStr[pos] == ' ') pos++;
            if (jsonStr[pos++] != '\"') return "";
            std::string value = "";
            while (pos < jsonStr.length() && jsonStr[pos] != '\"') value += jsonStr[pos++];
            return value;
        }
    }
    return "";
}

std::string RequestUtils::getFileAsString(const std::string &fileName) {
    std::string fileName2;
    if (fileName[0] == '/') {
        fileName2 = fileName.substr(1);
    } else {
        fileName2 = fileName;
    }
    std::ifstream file(fileName2);
    if (!file.good()) {
        throw "File not found";
    }
    std::string res = "";
    std::string line;
    while (std::getline(file, line)) {
        res += line + "\r\n";
    }
    return res;
}

std::vector<std::string> RequestUtils::parseRequestUri(const std::string uri) {
    std::vector<std::string> dirs;
    for (int i = 0; i < uri.length(); i++) {
        if (uri[i] == '/') {
            dirs.push_back("");
        } else {
            dirs.back() += uri[i];
        }
    }
    while (dirs.size() > 0 && dirs.back().length() == 0) {
        dirs.pop_back();
    }
    return dirs;
}

std::string RequestUtils::getFileExtension(const std::string &file) {
    int pos = file.length() - 1;
    for (; pos >= 0 && file[pos] != '/'; pos--) {
        if (file[pos] == '.') {
            return file.substr(pos);
        }
    }
    return "";
}
