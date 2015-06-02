#ifndef SERVER_H
#define SERVER_H

#include <set>
#include <functional>
#include <signal.h>
#include <memory>
#include <vector>

#include "../tcpconnection.h"
#include "../epollhandler.h"

class server {  
    TCPConnection tcpConnection;
    TCPSocket listener; // listening socket
    std::function<void(TCPSocket&)> onAccept;
    std::vector<TCPSocket> clients;
public:
    server(char *addr, char *port, int maxClientsCount, std::function<void(TCPSocket&)>,
           EpollHandler &epoll);
    ~server();
};

#endif // SERVER_H
