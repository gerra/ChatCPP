//
// Created by german on 05.06.15.
//

#include "Chat.h"

void Chat::addMessage(const Message &message) {
    messages.push_back(message);
}

void Chat::addUser(const std::string &user) {
    if (user.length() != 0 && users.find(user) == users.end()) {
        users.insert(user);
    }
}

std::vector<Message> &Chat::getMessages() {
    return messages;
}
