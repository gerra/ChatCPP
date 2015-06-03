//
// Created by german on 03.06.15.
//

#ifndef CHATCPP_REQUESTUTILS_H
#define CHATCPP_REQUESTUTILS_H


#include <string>
#include <vector>

class RequestUtils {
public:
    static std::vector<std::string> splitStringBySpace(const std::string &s);
    static bool isGetRequest(const std::string &s);
};


#endif //CHATCPP_REQUESTUTILS_H
