//
// Created by german on 03.06.15.
//

#include "HTTPServer.h"
#include "../TCPServer/TCPServer.h"
#include "RequestUtils.h"
#include "../model/HTTPException.h"

void HTTPServer::addBufToString(std::string &s, const char *buf, int n) {
    for (int i = 0; i < n; i++) {
        s += *(buf +i);
    }
}

HTTPServer::HTTPServer(char *addr, char *port, int maxClientsCount,
                       std::function<HTTPResponse(HTTPRequest &request)> onGet,
                       std::function<HTTPResponse(HTTPRequest &request)> onPost,
                       EpollHandler &epoll) {
    std::function<void(TCPSocket &)> onAccept = [&onGet, &onPost, this](TCPSocket &sock) {
        const int BUF_MAX_SIZE = 4096;
        char buf[BUF_MAX_SIZE];

        int len;
        while (true) {
            len = sock.recieveMsg(buf, BUF_MAX_SIZE);
            if (len <= 0) break;
            addBufToString(currentRequest, buf, len);
        }

        HTTPRequest httpRequest;
        HTTPResponse httpResponse;
        try {
            std::cout << currentRequest << "\n";
            httpRequest = HTTPRequest(currentRequest);

            std::cout << "Request from soket " << sock.sockfd << ": " << currentRequest << "\n";
            if (httpRequest.getMethod() == "GET") {
                httpResponse = onGet(httpRequest);
            } else if (httpRequest.getMethod() == "POST") {
                httpResponse = onPost(httpRequest);
            }
        } catch (HTTPException &e) {
            std::cerr << "Bad HTTP Request: " << e.getMessage() << "\n";

            httpResponse.setHttpVersion("HTTP/1.1");
            httpResponse.setStatusCode(400);
            httpResponse.setReasonPhrase("Bad request format!");
            httpResponse.addEntityHeader("Content-Type", "text/html");
        }
        std::cout << "Response for socket " << sock.sockfd << ": " << httpResponse.buildResponse() << "\n";
        sock.sendMsg(httpResponse.buildResponse().c_str());
        currentRequest = "";
    };
    tcpServer = new TCPServer(addr, port, maxClientsCount * 2, onAccept, epoll);
}

HTTPServer::~HTTPServer() {
    delete tcpServer;
}