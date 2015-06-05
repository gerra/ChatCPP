//
// Created by german on 05.06.15.
//

#ifndef CHATCPP_CHAT_H
#define CHATCPP_CHAT_H


#include "Message.h"
#include <vector>
#include <set>

class Chat {
    std::vector<Message> messages;
    std::set<std::string> users;
public:
    void addMessage(const Message &message);
    void addUser(const std::string &user);
    std::vector<Message> &getMessages();
};


#endif //CHATCPP_CHAT_H
