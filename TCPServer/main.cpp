#include "TCPServer.h"

void addBufToString(std::string &s, const char *buf, int n) {
    for (int i = 0; i < n; i++) {
        s += *(buf + i);
    }
}

int main() {
    std::string request;
    std::function<void(TCPSocket &)> onAccept = [&request](TCPSocket &sock) {
        char buf[1024];

        int len;
        len = sock.recieveMsg(buf, 1);
        addBufToString(request, buf, len);
        if (buf[len - 1] == '\n') {
            std::cout << "Request from socket " << sock.sockfd << ": " << request << "\n";
            request = "";
        }
    };
    try {
        EpollHandler IOLoop(1024);

        TCPServer myServer1("127.0.0.1", "2323", 10, onAccept, IOLoop);

        IOLoop.run();
    } catch (TCPException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (EpollException& e) {
        std::cerr << e.getMessage() << "\n";
    }

    std::cout << "Finish\n";
    return 0;
}
