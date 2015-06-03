#include <cassert>
#include "epollhandler.h"

EpollHandler::EpollHandler(int maxCount) {
    epollFD = epoll_create(maxCount);
    if (epollFD == -1) {
        perror("epoll_create");
        throw TCPException("Creating epoll error");
    }
}

EpollHandler::~EpollHandler() {
    if (epollFD >= 0) {
        int res = close(epollFD);
        assert(res != -1);
    }
}

void EpollHandler::run() {
    signal(SIGINT, EpollHandler::signal_int);
    std::cerr << "Starting EpollHandler: " << "\n";
    for (;;) {
        if (flag) break;

        const int MAX_EVENTS = 10;
        epoll_event events[MAX_EVENTS];
        int nfds = getEvents(events, MAX_EVENTS);
        if (nfds < 0) {
            return;
        }
        std::cerr << "changed " << nfds << " sockets:" << "\n";
        for (int i = 0; i < nfds; i++) {
            int curFD = events[i].data.fd;
            std::cerr << "   " << curFD << "changed" << "\n";
            std::uint32_t curEvents = events[i].events;
            if (handlers.find(curFD) != handlers.end()) {
                handlers[curFD].handle(curEvents);
            }
        }
    }
}

void EpollHandler::addSocketToEpoll(TCPSocket &socket, std::uint32_t events, Handler handler) {
    epoll_event ev;
    int sockfd = socket.sockfd;
    ev.data.fd = sockfd;
    ev.events = events | EPOLLRDHUP | EPOLLHUP | EPOLLERR | EPOLLIN;
    if ((epoll_ctl(epollFD, EPOLL_CTL_ADD, sockfd, &ev)) == -1) {
        perror("epolBl_ctl");
        throw EpollException("Adding socket to epoll error");
    }
    handlers[sockfd] = handler;
    std::cerr << "Added to epoll: " << sockfd << "\n";
}

void EpollHandler::signal_int(int) {
    static EpollHandler loop(1024);
    loop.flag = true;
}

int EpollHandler::getEvents(epoll_event *events, int maxEventsCount, int timeout) {
    return epoll_wait(epollFD, events, maxEventsCount, timeout);
}

void EpollHandler::onClose(int fd) {
    if ((epoll_ctl(epollFD, EPOLL_CTL_DEL, fd, NULL)) == -1) {
        perror("epoll_ctl");
    }
    std::cerr << "epolldel starts" << "\n";
    handlers.erase(fd);
    std::cerr << "epolldel endsmap erase" << "\n";
}

void EpollHandler::onDelete(int fd) {
    //onClose(fd);
    // if it' deleting |=> it was closed
}
