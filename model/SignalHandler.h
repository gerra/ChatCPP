//
// Created by german on 07.06.15.
//

#ifndef CHATCPP_SIGNALHANDLER_H
#define CHATCPP_SIGNALHANDLER_H


#include <functional>
#include "epollhandler.h"

class SignalHandler {
public:
    static void registerEpollHandler(EpollHandler *epollHandler);
    static void unregisterEpollHandler();
    static void registerSignal(int signal, void (*handler)(int));
    static void unregister_signal(int signal);

    static void signal_int(int signal);
    static void signal_term(int signal);
private:
    static EpollHandler *epollHandler;
};


#endif //CHATCPP_SIGNALHANDLER_H
