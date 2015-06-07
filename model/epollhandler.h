#ifndef EPOLLHANDLER_H
#define EPOLLHANDLER_H

#include <sys/epoll.h>
#include "handler.h"
#include "tcpsocket.h"
#include <map>

#include <csignal>

class EpollException : std::exception {
    std::string msg;
public:
    EpollException(std::string msg) : msg(msg) {}
    EpollException(const char *msg) : msg(msg) {}
    std::string getMessage() {
        return msg;
    }
};

class EpollHandler : TCPSocket::Listener {
    bool running;
    int epollFD;
    std::map<int, Handler> handlers;
    std::map<int, TCPSocket> sockets;
    int getEvents(epoll_event *events, int maxActionsCount, int timeout = -1);

    volatile sig_atomic_t flag = 0;
    static void signal_int(int);
public:
    EpollHandler(int maxCount);
    void stop();
    ~EpollHandler();

    void run();

    void addSocketToEpoll(TCPSocket &socket, std::uint32_t events, Handler handler);

    void onClose(int fd);
};

#endif // EPOLLHANDLER_H
