//
// Created by german on 04.06.15.
//

#ifndef CHATCPP_HTTPEXCEPTION_H
#define CHATCPP_HTTPEXCEPTION_H


#include <exception>
#include <string>

class HTTPException : std::exception {
private:
    std::string msg;
public:
    HTTPException(std::string msg) : msg(msg) {}
    HTTPException(const char *msg) : msg(msg) {}
    std::string getMessage() {
        return msg;
    }
};

#endif //CHATCPP_HTTPEXCEPTION_H
