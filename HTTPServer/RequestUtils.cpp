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