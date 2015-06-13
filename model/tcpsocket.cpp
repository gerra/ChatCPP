#include "tcpsocket.h"
#include "epollhandler.h"
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
        throw TCPException("Failed to set socket option for reusing address");
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
        perror("connect");
        throw TCPException("Failed to connect");
    }
}

int TCPSocket::setNonBlocking() {
    int flags = 0;
    if ((flags = fcntl(sockfd, F_GETFL, 0)) == -1) {
        flags = 0;
        perror("fcntl, get flags");
    }
    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}


void TCPSocket::sendMsgOnReady() {
    const char *msg = forSending.c_str();
    int msgSize = strlen(msg);

    std::cout << "Sending " << msgSize << " bytes:\n" << "\n";
    int totalSent = 0;
    int sent;
    while ((sent = send(sockfd, msg + totalSent, msgSize - totalSent < 1024 ? msgSize - totalSent : 1024, 0)) > 0) {
        totalSent += sent;
    }

    std::cout << "======= Sending finished (sent " << totalSent << " bytes) =======\n";
    std::cout << "___________________________________________________________________________\n";

    forSending = forSending.substr(totalSent);

    int success = totalSent == msgSize ? 1 : 0;
    for (auto listener : listeners) {
        listener->onWriteData(sockfd, success);
    }
}

void TCPSocket::sendMsg(const char *msg) {
    forSending += std::string(msg);
}

int TCPSocket::recieveMsg(char * buf, int maxSize) const {
    std::cerr << "Recieve from " << sockfd << "\n";
    int nbytes;
    if ((nbytes = recv(sockfd, buf, maxSize, 0)) == 0) {
        fprintf(stdout, "socket %d hung up\n", sockfd);
    }
    if (nbytes != 0) buf[nbytes] = '\0';
    std::cout  << "========= Received " << nbytes << ": =========\n";
    std::cout << buf << "\n";
    std::cout << "====================================\n";
    for (auto listener : listeners) {
        listener->onReadData(sockfd, nbytes);
    }
    return nbytes;
}

void TCPSocket::startListening(int count) const {
    if (listen(sockfd, count) == -1) {
        perror("listen");
        throw TCPException("Listen error");
    }
}

TCPSocket *TCPSocket::acceptNewSocket(sockaddr *addr, socklen_t *len) const {
    int newFD = accept(sockfd, addr, len);
    std::cerr << newFD << " accepted from " << sockfd << "\n" << "\n";
    if (newFD == -1) {
        perror("accept");
        throw TCPException("Unnable to accept");
    } else {
        return new TCPSocket(newFD);
    }
}
