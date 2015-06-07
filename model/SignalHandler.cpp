//
// Created by german on 07.06.15.
//

#include "SignalHandler.h"

EpollHandler *SignalHandler::epollHandler;

void SignalHandler::registerEpollHandler(EpollHandler *epollHandler) {
    SignalHandler::epollHandler = epollHandler;
}

void SignalHandler::unregisterEpollHandler() {
    SignalHandler::epollHandler = NULL;
}

void SignalHandler::registerSignal(int signal, void (*handler)(int)) {
    static struct sigaction term;
    term.sa_handler = handler;
    term.sa_flags = SA_SIGINFO;
    if (sigaction(signal, &term, NULL) == -1) {
        throw std::runtime_error("Could not connect signal");
    }
}

void SignalHandler::unregister_signal(int signal) {
    static struct sigaction term;
    term.sa_handler = SIG_DFL;
    term.sa_flags = SA_SIGINFO;
    if (sigaction(signal, &term, NULL) == -1) {
        throw std::runtime_error("Could not connect signal");
    }
}

void SignalHandler::signal_int(int signal) {
    if (SignalHandler::epollHandler != NULL) {
        SignalHandler::epollHandler->stop();
    }
}

void SignalHandler::signal_term(int signal) {
    if (SignalHandler::epollHandler != NULL) {
        SignalHandler::epollHandler->stop();
    }
}
