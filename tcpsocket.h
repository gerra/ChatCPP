#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <netdb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <functional>
#include "tcpexception.h"
#include <vector>
#include <iostream>

class EpollHandler;

class TCPSocket {
public:
    struct Listener {
        virtual void onClose(int fd) = 0;
    };

private:
    TCPSocket(int fd);
    std::vector<Listener*> listeners;

public:
    void addListener(Listener *listener) {
        std::cerr << "Listener added to socket" << sockfd << "\n";
        listeners.push_back(listener);
    }

    int sockfd;

    friend class EpollHandler;
    friend class Handler;

    TCPSocket() {
        sockfd = -1;
    }

    TCPSocket(const TCPSocket& other) = delete;
    TCPSocket(TCPSocket&& other) {
        sockfd = other.sockfd;
        other.sockfd = -1;
    }

    TCPSocket& operator=(const TCPSocket& other) {
        sockfd = other.sockfd;
    }
    TCPSocket& operator=(TCPSocket&& other) {
        sockfd = other.sockfd;
        other.sockfd = -1;
        return *this;
    }

    ~TCPSocket();
    TCPSocket(addrinfo *addr);

    void bindSocket(addrinfo *addr);
    void connectToAddr(addrinfo *addr);
    void reusePort();
    int setNonBlocking();
    void sendMsg(const char *msg) const;
    int recieveMsg(char * buf, int maxSize) const;
    void startListening(int count) const;
    TCPSocket *acceptToNewSocket(sockaddr *addr, socklen_t *len) const;

};

#endif // TCPSOCKET_H
