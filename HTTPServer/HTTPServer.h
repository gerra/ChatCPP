//
// Created by german on 03.06.15.
//

#ifndef CHATCPP_HTTPSERVER_H
#define CHATCPP_HTTPSERVER_H


#include "../model/epollhandler.h"
#include "../TCPServer/TCPServer.h"
#include "../model/HTTPResponse.h"
#include "../model/HTTPRequest.h"

class HTTPServer {
    TCPServer *tcpServer;
    std::map<int, std::string> currentRequest;
    void addBufToString(std::string &s, const char *buf, int n);
public:
    HTTPServer(const std::string &addr, const std::string &port, int maxClientsCount,
               std::function<HTTPResponse(HTTPRequest &request)> onGet,
               std::function<HTTPResponse(HTTPRequest &request)> onPost,
               EpollHandler &epoll);
    ~HTTPServer();
};


#endif //CHATCPP_HTTPSERVER_H
