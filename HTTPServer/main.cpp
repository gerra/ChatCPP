//
// Created by german on 03.06.15.
//

#include "HTTPServer.h"
#include "../epollhandler.h"
#include "../TCPServer/TCPServer.h"

int main() {
    try {
        EpollHandler IOLoop(1024);
        std::function<std::string(TCPSocket &, std::string &)> onGet = [] (TCPSocket &sock, std::string &request) -> std::string {
            std::string res = "";
            res += "HTTP/1.0 302 Found\r\n";
            res += "Content-Type: text/html; charset=UTF-8\r\nContent-Length: 256\r\n";
            res += "Date: Wed, 03 Jun 2015 00:42:14 GMT\r\nServer: GFE/2.0\r\nAlternate-Protocol: 80:quic,p=0\r\n\r\n";
            res += "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n";
            res += "<TITLE>302 Moved</TITLE></HEAD><BODY>\r\n<H1>302 Moved</H1>\r\nThe document has moved\r\n<A HREF=\"http://www.google.ru/?gfe_rd=cr&amp;ei=Zk1uVYO5MNGANJqIgNgE\">here</A>.\r\n";
            res += "</BODY></HTML>\r\n";
            //return "<html><title>HELLO!</title>WTF</html>\n";
            return res;
        };

        HTTPServer server = HTTPServer("127.0.0.1", "2323", 10, onGet, IOLoop);
        //TCPServer myServer1("127.0.0.1", "2323", 10, NULL, IOLoop);

        IOLoop.run();
    } catch (TCPException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (EpollException& e) {
        std::cerr << e.getMessage() << "\n";
    }

    std::cout << "Finish\n";
    return 0;
}
