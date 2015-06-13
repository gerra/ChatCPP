#include "TCPServer.h"

TCPServer::TCPServer(const char *addr, const char *port, int maxClientsCount, std::function<void (TCPSocket &)> onAccept,
               EpollHandler &epoll) {
    try {
        listener = NULL;
        tcpConnection.createAddress(addr, port);
        listener = tcpConnection.createBindingSocket();
        listener->setNonBlocking();
        listener->startListening(maxClientsCount);
        listener->addListener((TCPSocket::Listener*)&epoll);
        std::cerr << "Server socket " << listener->sockfd << "\n";

        epoll.addSocketToEpoll(
                    *listener,
                    EPOLLIN,
                    Handler([=, &epoll](int events) {
                        if (!(events & EPOLLIN)) return;
                        // events is EPOLLIN
                        std::cerr << "New connection on listener socket" << "\n";
                        sockaddr_storage theirAddr;
                        socklen_t addrLen;
                        addrLen = sizeof(theirAddr);
                        try {
                            TCPSocket *clientSocket = listener->acceptNewSocket((sockaddr *) &theirAddr, &addrLen);
                            clientSocket->addListener((TCPSocket::Listener*)&epoll);
                            clientSocket->setNonBlocking();
                            clients[clientSocket->sockfd] = clientSocket;
                            Handler clientHandler = Handler([=](int events) {
                                                try {
                                                    std::cerr << "New event on " << clientSocket->sockfd << "\n";
                                                    if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                                                        std::cerr << "client closed connection" << "\n";
                                                        deleteClient(clientSocket);
                                                    } else if (events & EPOLLIN) {
                                                        onAccept(*clientSocket);
                                                    } else if (events & EPOLLOUT) {
                                                        clientSocket->sendMsgOnReady();
                                                    }
                                                } catch (...) {
                                                    std::cerr << "!!! User thrown an exception !!!\n";
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
    std::cerr << "Deleting TCPServer" << "\n";
    while (!clients.empty()) {
        deleteClient(clients.begin()->second);
    }
    if (listener != NULL) {
        delete listener;
    }
}

void TCPServer::deleteClient(TCPSocket *client) {
    if (clients.find(client->sockfd) != clients.end()) {
        clients.erase(client->sockfd);
        delete client;
    }
}
