//
// Created by german on 05.06.15.
//

#ifndef CHATCPP_MESSAGE_H
#define CHATCPP_MESSAGE_H


#include "User.h"

class Message {
    std::string userName;
    std::string message;

public:
    Message(const std::string &userName, const std::string &message) : userName(userName), message(message) { }
};


#endif //CHATCPP_MESSAGE_H
