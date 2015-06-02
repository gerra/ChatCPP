#include "server.h"

server::server(char *addr, char *port, int maxClientsCount, std::function<void (TCPSocket &)> onAccept,
               EpollHandler &epoll) {
    try {
        tcpConnection.createAddress(addr, port);
        listener = tcpConnection.createBindingSocket();
        listener.setNonBlocking();
        listener.startListening(maxClientsCount);
        listener.addListener((TCPSocket::Listener*)&epoll);
        this->onAccept = onAccept;
        std::cerr << listener.sockfd <<  "(listener)" << "\n";
        epoll.addSocketToEpoll(
                    listener,
                    EPOLLIN,
                    Handler([=, &epoll](int events) {
                        // check events is EPOLLIN
                        std::cerr << "I'm listener of new connections" << "\n";
                        sockaddr_storage theirAddr;
                        socklen_t addrLen;
                        addrLen = sizeof(theirAddr);
                        try {
//                            TCPSocket clientSocket = listener.acceptToNewSocket((sockaddr *)&theirAddr, &addrLen);
//                            TCPSocket& clientSocket = listener.acceptToNewSocket((sockaddr *)&theirAddr, &addrLen);
                            clients.push_back(listener.acceptToNewSocket((sockaddr *)&theirAddr, &addrLen));
                            TCPSocket& clientSocket = clients.back();
                            clientSocket.addListener((TCPSocket::Listener*)&epoll);
                            clientSocket.setNonBlocking();
                            Handler clientHandler = Handler([=, &clientSocket](int events) {
                                                try {
                                                    std::cerr << "OnAccept" << clientSocket.sockfd << "\n";
                                                    if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                                                        std::cerr << "client closed connection" << "\n";
                                                        clientSocket.closeSocket();
                                                    } else {
                                                        onAccept(clientSocket);
                                                    }
                                                } catch (...) {
                                                    clientSocket.closeSocket();
                                                    throw;
                                                }
                                            });
                            epoll.addSocketToEpoll(
                                        clientSocket,
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

server::~server() {
    std::cerr << "deleting server starts..." << "\n";
    listener.closeSocket();
    std::cerr << "...deleting server ends" << "\n";
}
