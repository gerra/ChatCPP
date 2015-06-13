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

class TCPSocket;
class EpollHandler : TCPSocket::Listener {
    int epollFD;
    std::map<int, Handler> handlers;
    int getEvents(epoll_event *events, int maxActionsCount, int timeout = -1);

    volatile sig_atomic_t flag = 0;
public:
    EpollHandler(const EpollHandler &other) = delete;

    ~EpollHandler();

    EpollHandler(int maxCount);
    void stop();
    void run();
    void addSocketToEpoll(TCPSocket &socket, std::uint32_t events, Handler handler);

    virtual void onClose(int fd) override;

private:
    virtual void onReadData(int fd, int nbytes) override;
    virtual void onWriteData(int fd, int nbytes) override;
};

#endif // EPOLLHANDLER_H
