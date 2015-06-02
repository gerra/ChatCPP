#ifndef HANDLER_H
#define HANDLER_H

#include <functional>

class Handler {
    std::function<void(int)> action;
public:
    Handler() {}
    Handler(std::function<void(int)> action);
    void handle(int events);
};

#endif // HANDLER_H
