//
// Created by german on 03.06.15.
//

#include "HTTPServer.h"
#include "../TCPServer/TCPServer.h"
#include "RequestUtils.h"

void HTTPServer::addBufToString(std::string &s, const char *buf, int n) {
    for (int i = 0; i < n; i++) {
        s += *(buf +i);
    }
}

HTTPServer::HTTPServer(char *addr, char *port, int maxClientsCount, std::function<std::string(TCPSocket &sock, std::string &request)> onGet,
           EpollHandler &epoll) {
    std::function<void(TCPSocket &)> onAccept = [&onGet, this](TCPSocket &sock) {
        const int BUF_MAX_SIZE = 4096;
        char buf[BUF_MAX_SIZE];

        int len;
        while (true) {
            len = sock.recieveMsg(buf, BUF_MAX_SIZE);
            if (len <= 0) break;
            addBufToString(currentRequest, buf, len);
        }

        std::cout << "Request from socket " << sock.sockfd << ": " << currentRequest << "\n";
        if (RequestUtils::isGetRequest(currentRequest)) {
            std::string response = onGet(sock, currentRequest);
            sock.sendMsg(response.c_str());
            std::cout << "Response for socket " << sock.sockfd << ": " << response << "\n";
        }
        currentRequest = "";
    };
    tcpServer = new TCPServer(addr, port, maxClientsCount * 2, onAccept, epoll);
}

HTTPServer::~HTTPServer() {
    delete tcpServer;
}