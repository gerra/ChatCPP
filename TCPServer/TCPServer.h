#ifndef SERVER_H
#define SERVER_H

#include <set>
#include <functional>
#include <signal.h>
#include <memory>
#include <vector>

#include "../tcpconnection.h"
#include "../epollhandler.h"

class TCPServer {
    TCPConnection tcpConnection;
    TCPSocket *listener; // listening socket
//    std::set<TCPSocket*> clients;
    std::map<int, TCPSocket *> clients;
    void deleteClient(TCPSocket *client);
public:

    TCPServer(char *addr, char *port, int maxClientsCount, std::function<void(TCPSocket&)>,
           EpollHandler &epoll);
    ~TCPServer();
};

#endif // SERVER_H
