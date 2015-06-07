#include "TCPServer.h"

TCPServer::TCPServer(char *addr, char *port, int maxClientsCount, std::function<void (TCPSocket &)> onAccept,
               EpollHandler &epoll) {
    try {
        listener = NULL;
        tcpConnection.createAddress(addr, port);
        listener = tcpConnection.createBindingSocket();
        listener->setNonBlocking();
        listener->startListening(maxClientsCount);
        listener->addListener((TCPSocket::Listener*)&epoll);
        std::cerr << listener->sockfd <<  "(listener)" << "\n";

        epoll.addSocketToEpoll(
                    *listener,
                    EPOLLIN,
                    Handler([=, &epoll](int events) {
                        // events is EPOLLIN
                        std::cerr << "I'm listener of new connections" << "\n";
                        sockaddr_storage theirAddr;
                        socklen_t addrLen;
                        addrLen = sizeof(theirAddr);
                        try {
                            TCPSocket *clientSocket = listener->acceptToNewSocket((sockaddr *)&theirAddr, &addrLen);
                            clientSocket->addListener((TCPSocket::Listener*)&epoll);
                            clientSocket->setNonBlocking();
                            clients[clientSocket->sockfd] = clientSocket;
                            Handler clientHandler = Handler([=](int events) {
                                                try {
                                                    std::cerr << "OnAccept" << clientSocket->sockfd << "\n";
                                                    if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                                                        std::cerr << "client closed connection" << "\n";
                                                        deleteClient(clientSocket);
                                                    } else {
                                                        onAccept(*clientSocket);
                                                    }
                                                } catch (...) {
                                                    std::cerr << "user thrown an exception\n";
                                                    deleteClient(clientSocket);
                                                    throw;
                                                }
                                            });
                            epoll.addSocketToEpoll(
                                        *clientSocket,
                                        EPOLLIN,
                                        clientHandler
                            );


                        } catch (TCPException &e) {
                            std::cerr << e.getMessage() << "\n";
                        } catch (EpollException &e) {
                            std::cerr << e.getMessage() << "\n";
                        }
                    })
        );

    } catch (TCPException &e) {
        std::cerr << e.getMessage() << "\n";
        throw;
    } catch (EpollException &e) {
        std::cerr << e.getMessage() << "\n";
        throw;
    }
}

TCPServer::~TCPServer() {
    std::cerr << "deleting TCPServer started..." << "\n";
    while (!clients.empty()) {
        deleteClient(clients.begin()->second);
    }
    delete listener;
    std::cerr << "...deleting TCPServer ended" << "\n";
}

void TCPServer::deleteClient(TCPSocket *client) {
    if (clients.find(client->sockfd) != clients.end()) {
        clients.erase(client->sockfd);
        delete client;
    }
}
