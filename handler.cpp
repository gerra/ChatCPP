#include "handler.h"

Handler::Handler(std::function<void(int)> action) {
    this->action = action;
}

void Handler::handle(int events) {
    action(events);
}
