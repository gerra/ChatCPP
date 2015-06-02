#include "server.h"

int main() {
    std::function<void(TCPSocket &)> onAccept = [](TCPSocket &sock) {
        char buf[500];
        sock.recieveMsg(buf, 1);
        std::cout << std::string(buf);
        if (buf[0] == '~' && buf[1] == 'd') {
            sock.closeSocket();
        } else {
            sock.sendMsg(buf);
        }
    };
    try {
        EpollHandler IOLoop(1024);

        server myServer1("127.0.0.1", "2323", 10, onAccept, IOLoop);
        server myServer2("127.0.0.1", "4646", 10, onAccept, IOLoop);
        server myServer3("127.0.0.1", "6969", 10, onAccept, IOLoop);

        IOLoop.run();
    } catch (TCPException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (EpollException& e) {
        std::cerr << e.getMessage() << "\n";
    }

    std::cout << "Finish\n";
    return 0;
}
