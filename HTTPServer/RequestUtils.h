//
// Created by german on 03.06.15.
//

#ifndef CHATCPP_REQUESTUTILS_H
#define CHATCPP_REQUESTUTILS_H


#include <string>
#include <vector>
#include <map>

class RequestUtils {
    static std::vector<std::string> requestMethods;
    static std::vector<std::string> generalHeaders;
    static std::vector<std::string> requestHeaders;
public:
    static std::vector<std::string> splitStringBySpace(const std::string &s);
    static bool isGetRequest(const std::string &s);
    static std::vector<std::string> &getRequestMethods();
    static std::vector<std::string> &getGeneralHeaders();
    static std::vector<std::string> &getRequestHeaders();
    static void addMapValuesToString(const std::map<std::string, std::string> &mp, std::string &s);
    static std::string getIntAsString(int x);
    static std::string getValueFromJsonByKey(const std::string &jsonStr, const std::string &key);
};

#endif //CHATCPP_REQUESTUTILS_H
