#include "HTTPServer.h"
#include "RequestUtils.h"

int main() {
    try {
        EpollHandler IOLoop(1024);
        std::function<HTTPResponse(TCPSocket &, HTTPRequest &)> onGet = [] (TCPSocket &sock, HTTPRequest &request) -> HTTPResponse {
            HTTPResponse httpResponse;
            httpResponse.setHttpVersion("HTTP/1.0");
            httpResponse.setStatusCode(200);
            httpResponse.setReasonPhrase("Found");
            httpResponse.addEntityHeader("Content-Type", "text/html; charset=UTF-8");

            std::string q = "";

            q += "<HTML>\r\n<BODY>\r\n";

            q += "<form action=\"http://127.0.0.1:2323\" method=\"post\">\r\n";
            q += "<input name=\"say\" value=\"Hi\">\r\n";
            q += "<input name=\"to\" value=\"Mom\">\r\n";
            q += "<button>Send my greetings</button>\r\n";
            q += "</form>\r\n";

            q += "</BODY>\r\n</HTML>\r\n";

//            q += "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n";
//            q += "<TITLE>302 Moved</TITLE></HEAD><BODY>\r\n<H1>302 Moved</H1>\r\nThe document has moved\r\n<A HREF=\"http://www.google.ru/?gfe_rd=cr&amp;ei=Zk1uVYO5MNGANJqIgNgE\">here</A>.\r\n";
//            q += "</BODY></HTML>\r\n";

            httpResponse.setMessageBody(q);
            return httpResponse;
        };

        std::function<HTTPResponse(TCPSocket &, HTTPRequest &)> onPost = [] (TCPSocket &sock, HTTPRequest &request) -> HTTPResponse {
            HTTPResponse httpResponse;
            httpResponse.setHttpVersion("HTTP/1.0");
            httpResponse.setStatusCode(302);
            httpResponse.setReasonPhrase("Found");
            httpResponse.addEntityHeader("Content-Type", "text/html; charset=UTF-8");

            std::string q = "";

            if () {

            } else {

            }

            q += "<HTML>\r\n<BODY>\r\n";

            q += "HUI\r\n";

            q += RequestUtils::getValueFromJsonByKey(request.getMessageBody(), "user");

            q += "\r\n";

            q += "</BODY>\r\n</HTML>\r\n";

//            q += "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n";
//            q += "<TITLE>302 Moved</TITLE></HEAD><BODY>\r\n<H1>302 Moved</H1>\r\nThe document has moved\r\n<A HREF=\"http://www.google.ru/?gfe_rd=cr&amp;ei=Zk1uVYO5MNGANJqIgNgE\">here</A>.\r\n";
//            q += "</BODY></HTML>\r\n";

            httpResponse.setMessageBody(q);
            return httpResponse;
        };

        HTTPServer server = HTTPServer("127.0.0.1", "2323", 10, onGet, onPost, IOLoop);
        //TCPServer myServer1("127.0.0.1", "2323", 10, NULL, IOLoop);

        IOLoop.run();
    } catch (TCPException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (EpollException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (...) {
    }

    std::cout << "Finish\n";
    return 0;
}
