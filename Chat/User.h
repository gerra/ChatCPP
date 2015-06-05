//
// Created by german on 05.06.15.
//

#ifndef CHATCPP_USER_H
#define CHATCPP_USER_H

#include <string>

class User {
    std::string name;
public:
    User(const std::string &name) : name(name) { }

    std::string getName();
};


#endif //CHATCPP_USER_H
