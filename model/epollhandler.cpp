#include "epollhandler.h"
#include "tcpsocket.h"
#include "SignalHandler.h"
#include <cassert>

EpollHandler::EpollHandler(int maxCount) {
    SignalHandler::registerEpollHandler(this);
    SignalHandler::registerSignal(SIGINT, &SignalHandler::signal_int);
    SignalHandler::registerSignal(SIGTERM, &SignalHandler::signal_term);
    epollFD = epoll_create(maxCount);
    if (epollFD == -1) {
        perror("epoll_create");
        throw TCPException("Creating epoll error");
    }
}

EpollHandler::~EpollHandler() {
    SignalHandler::unregister_signal(SIGINT);
    SignalHandler::unregister_signal(SIGTERM);
    SignalHandler::unregisterEpollHandler();
    if (epollFD >= 0) {
        int res = close(epollFD);
        assert(res != -1);
    }
}

void EpollHandler::run() {
   // signal(SIGINT, EpollHandler::signal_int);
    std::cerr << "Starting EpollHandler" << "\n";
    for (;;) {
        if (flag) break;

        const int MAX_EVENTS = 10;
        epoll_event events[MAX_EVENTS];
        int nfds = getEvents(events, MAX_EVENTS);
        if (nfds < 0) {
            return;
        }
        std::cerr << "Changed " << nfds << " sockets" << "\n";
        for (int i = 0; i < nfds; i++) {
            int curFD = events[i].data.fd;
            std::cerr << "   " << curFD << " changed" << "\n";
            std::uint32_t curEvents = events[i].events;
            if (handlers.find(curFD) != handlers.end()) {
                handlers[curFD].handle(curEvents);
            }
        }
    }
}

void EpollHandler::addSocketToEpoll(TCPSocket &socket, std::uint32_t events, Handler handler) {
    epoll_event ev = {};
    int sockfd = socket.sockfd;
    ev.data.fd = sockfd;
    ev.events = events | EPOLLRDHUP | EPOLLHUP | EPOLLERR | EPOLLIN;
    if ((epoll_ctl(epollFD, EPOLL_CTL_ADD, sockfd, &ev)) == -1) {
        perror("addSocketToEpoll_epoll_ctl");
        throw EpollException("Adding socket to epoll error");
    }
    handlers[sockfd] = handler;
    std::cerr << sockfd << " added to epoll" << "\n";
}

int EpollHandler::getEvents(epoll_event *events, int maxEventsCount, int timeout) {
    return epoll_wait(epollFD, events, maxEventsCount, timeout);
}

void EpollHandler::onClose(int fd) {
    std::cerr << "Deleting " << fd << " from epoll\n";
    if ((epoll_ctl(epollFD, EPOLL_CTL_DEL, fd, NULL)) == -1) {
        perror("onClose_epoll_ctl");
    }
    handlers.erase(fd);
}

void EpollHandler::stop() {
    flag = true;
}

void EpollHandler::onReadData(int fd, int nbytes) {
    epoll_event event = {};
    event.data.fd = fd;
    event.events = nbytes == 0 ? 0 : EPOLLOUT;
    if (epoll_ctl(epollFD, EPOLL_CTL_MOD, fd, &event) < 0) {
        perror("epoll set mode");
    }
}

void EpollHandler::onWriteData(int fd, int nbytes) {
    epoll_event event = {};
    event.data.fd = fd;
    event.events = nbytes == 1 ? EPOLLIN : EPOLLOUT;
    if (epoll_ctl(epollFD, EPOLL_CTL_MOD, fd, &event) < 0) {
        perror("epoll set mode");
    }
}
