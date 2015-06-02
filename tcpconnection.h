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


#include "tcpsocket.h"
#include "tcpexception.h"

class TCPConnection {
    addrinfo hints;
    addrinfo *res;
public:
    TCPConnection();
    ~TCPConnection();
    void createAddress(char * address, char * port);
    // these 2 functions return socket file descriptor
    TCPSocket createConnection();
    TCPSocket createBindingSocket();
};

/*
 * returns:
 *  < 0 if error
 *  = 0 if fd was closed
 *  > 0 is msgSize
 */

std::string getAddrAsString(sockaddr_storage &addr);

#endif // TCPCONNECTION_H