//
// Created by german on 03.06.15.
//

#ifndef CHATCPP_HTTPSERVER_H
#define CHATCPP_HTTPSERVER_H


#include "../epollhandler.h"
#include "../TCPServer/TCPServer.h"

class HTTPServer {
    TCPServer *tcpServer;
    std::string currentRequest;
    void addBufToString(std::string &s, const char *buf, int n);
public:
    HTTPServer(char *addr, char *port, int maxClientsCount, std::function<std::string(TCPSocket &sock, std::string &request)> onGet,
               EpollHandler &epoll);
    ~HTTPServer();
};


#endif //CHATCPP_HTTPSERVER_H
