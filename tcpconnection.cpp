#include "tcpconnection.h"

TCPConnection::TCPConnection() {
}

void TCPConnection::createAddress(char *address, char *port) {
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // whatever ipv4 or ipv6
    hints.ai_socktype = SOCK_STREAM; // tcp connection
    int rv;
    if ((rv = getaddrinfo(address, port, &hints, &res)) != 0) {
        throw TCPException("getaddrinfo: " + std::string(gai_strerror(rv)));
    }
}

TCPSocket TCPConnection::createConnection() {
    addrinfo * stableAddr = NULL;
    TCPSocket resultSocket;
    for (stableAddr = res; stableAddr != NULL; stableAddr = stableAddr->ai_next) {
        if (stableAddr->ai_socktype != SOCK_STREAM) {
            continue;
        }
        try {
            resultSocket = TCPSocket(stableAddr);
        } catch (TCPException &e) {
            resultSocket.closeSocket();
            continue;
        }

        try {
            resultSocket.connectToAddr(stableAddr);
        } catch (TCPException &e) {
            resultSocket.closeSocket();
            continue;
        }
        break; // we found good address
    }
    if (stableAddr == NULL) {
        resultSocket.closeSocket();
        throw TCPException("Failed to connect");
    }
    return resultSocket;
}

TCPSocket TCPConnection::createBindingSocket() {
    addrinfo *stableAddr = NULL;

    TCPSocket resultSocket;
    for (stableAddr = res; stableAddr != NULL; stableAddr = stableAddr->ai_next) {
        if (stableAddr->ai_socktype != SOCK_STREAM) {
            continue;
        }
        try {
            resultSocket = TCPSocket(stableAddr);
        } catch (TCPException &e) {
            resultSocket.closeSocket();
            continue;
        }

        try {
            resultSocket.reusePort();
        } catch (TCPException &e) {
            resultSocket.closeSocket();
            throw;
        }

        try {
            resultSocket.bindSocket(stableAddr);
        } catch (TCPException &e) {
            resultSocket.closeSocket();
            continue;
        }
        break;
    }

    if (stableAddr == NULL) {
        resultSocket.closeSocket();
        throw TCPException("Failed to bind");
    }
    return resultSocket;
}

TCPConnection::~TCPConnection() {
    freeaddrinfo(res);
}

void *getInAddr(sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((sockaddr_in*)sa)->sin_addr);
    }
    return &(((sockaddr_in6*)sa)->sin6_addr);
}

std::string getAddrAsString(sockaddr_storage &addr) {
    char s[INET6_ADDRSTRLEN];
    inet_ntop(addr.ss_family, getInAddr((sockaddr*)&addr), s, sizeof(s));
    std::string ss(s);
    return ss;
}
