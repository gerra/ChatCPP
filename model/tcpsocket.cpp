#include "tcpsocket.h"
#include <assert.h>
#include <iostream>
#include <fcntl.h>

TCPSocket::TCPSocket(int fd) {
    sockfd = fd;
}

TCPSocket::TCPSocket(addrinfo *addr) {
    if (addr->ai_socktype != SOCK_STREAM) {
        throw TCPException("Bad socket type");
    }
    sockfd = socket(addr->ai_family,
                    addr->ai_socktype,
                    addr->ai_protocol);
    if (sockfd == -1) {
        perror("socket");
        throw TCPException("Failed to create socket");
    }
}

TCPSocket::~TCPSocket() {
    std::cerr << "Deleting socket " << sockfd << "\n";
//    if (sockfd >= 0) {
//        std::cerr << "Closing socket " << sockfd << "\n";
//        for (auto *it : listeners) {
//            it->onClose(sockfd);
//        }
//        int res = close(sockfd);
//        assert(res != -1);
//        sockfd = -1;
//    }
    if (sockfd >= 0) {
        std::cerr << "Closing socket " << sockfd << ", " << listeners.size() << " listeners" << "\n";
        for (auto listener : listeners) {
            listener->onClose(sockfd);
        }
        if (sockfd != -1) {
            int res = close(sockfd);
            assert(res != -1);
            sockfd = -1;
        }
    }
}

void TCPSocket::reusePort() {
    // reusing the port
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                   &yes, sizeof(int)) == -1) {
        perror("setsockport");
        throw TCPException("Failed to set socket on port");
    }
}

void TCPSocket::bindSocket(addrinfo *addr) {
    int res = bind(sockfd, addr->ai_addr, addr->ai_addrlen);
    if (res == -1) {
        perror("bind");
        throw TCPException("Failed to bind");
    }
}

void TCPSocket::connectToAddr(addrinfo *addr) {
    int res = connect(sockfd, addr->ai_addr, addr->ai_addrlen);
    if (res == -1) {
        perror("connect: ");
        throw TCPException("Failed to connect");
    }
}

int TCPSocket::setNonBlocking() {
    int flags;
    /* If they have O_NONBLOCK, use the Posix way to do it */
    /* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
    if (-1 == (flags = fcntl(sockfd, F_GETFL, 0))) {
        flags = 0;
    }
    return {
        fcntl(sockfd, F_SETFL, flags | O_NONBLOCK)
    };
}

void TCPSocket::sendMsg(const char *msg) const {
    int msgSize = strlen(msg);
    if (send(sockfd, msg, msgSize, 0) == -1) {
        perror("send");
        throw TCPException("Sending error");
    }
}

int TCPSocket::recieveMsg(char * buf, int maxSize) const {
    std::cerr << "Recieve from " << sockfd << "\n";
    int nbytes;
    if ((nbytes = recv(sockfd, buf, maxSize, 0)) <= 0) {
        if (nbytes == 0) {
            fprintf(stdout, "socket %d hung up\n", sockfd);
            return 0;
        } else {
            perror("recv");
            //throw TCPException("Recieving error");
        }
    }
    buf[nbytes] = '\0';
    std::cerr << "received " << nbytes << "\n";
    return nbytes;
}

void TCPSocket::startListening(int count) const {
    if (listen(sockfd, count) == -1) {
        perror("listen");
        throw TCPException("Listen error");
    }
}

TCPSocket *TCPSocket::acceptToNewSocket(sockaddr *addr, socklen_t *len) const {
    int newFD = accept(sockfd, addr, len);
    std::cerr << newFD << " accepting from" << sockfd << "\n" << "\n";
    if (newFD == -1) {
        perror("accept");
        throw TCPException("Unnable to accept");
    } else {
        return new TCPSocket(newFD);
    }
}
