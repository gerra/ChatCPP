#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <netdb.h>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <iostream>


#include "model/tcpsocket.h"

class TCPConnection {
    addrinfo hints;
    addrinfo *res;
public:
    TCPConnection();
    ~TCPConnection();
    void createAddress(const char * address, const char * port);
//    TCPSocket createConnection();
    TCPSocket *createBindingSocket();
};

std::string getAddrAsString(sockaddr_storage &addr);

#endif // TCPCONNECTION_H
