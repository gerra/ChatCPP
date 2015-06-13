#include "HTTPServer.h"
#include "RequestUtils.h"
#include "../Chat/Chat.h"
#include "../model/HTTPException.h"

Chat chat;
HTTPResponse defaultResponse;

int main() {
    defaultResponse.setHttpVersion("HTTP/1.1");
    defaultResponse.setStatusCode(404);
    defaultResponse.setReasonPhrase("Not found");
    defaultResponse.addEntityHeader("Content-Type", "*/*");
    defaultResponse.addResponseHeader("Access-Control-Allow-Origin", "*");
    try {
        EpollHandler IOLoop(1024);

        std::function<HTTPResponse(HTTPRequest &)> onGet = [] (HTTPRequest &request) -> HTTPResponse {
            HTTPResponse httpResponse;
            httpResponse.setHttpVersion("HTTP/1.1");

            std::vector<std::string> path = RequestUtils::parseRequestUri(request.getRequestUri());
            if (path.size() == 1 && path.back() == "messages") {
                std::vector<Message> &messages = chat.getMessages();
                std::string text = "[";
                int from = messages.size() - 15;
                if (from < 0) {
                    from = 0;
                }
                for (int i = from; i < messages.size(); i++) {
                    auto &message = messages[i];
//                for (auto &message : chat.getMessages()) {
                    text += "{";
                    text += "\"user\":";
                    text += "\"" + message.getUserName() + "\"";
                    text += ",";
                    text += "\"message\":";
                    text += "\"" + message.getMessage() + "\"";
                    text += "},";
                }
                if (text.back() != '[') {
                    text.back() = ']'; // replace last comma
                } else {
                    text += "]";
                }
                httpResponse.setStatusCode(200);
                httpResponse.setReasonPhrase("OK");
                httpResponse.addEntityHeader("Content-Type", "application/json; charset=UTF-8");
                httpResponse.addResponseHeader("Access-Control-Allow-Origin", "*");
                httpResponse.setMessageBody(text);
            } else if (path.size() == 0) {
                httpResponse.setStatusCode(200);
                httpResponse.setReasonPhrase("OK");
                httpResponse.setMessageBody(RequestUtils::getFileAsString("chat.html"));
                httpResponse.addEntityHeader("Content-Type", "text/html");
                httpResponse.addResponseHeader("Access-Control-Allow-Origin", "*");
            } else {
                if (path.size() > 0) {
                    try {
                        // try to send a file
                        httpResponse.setMessageBody(RequestUtils::getFileAsString(request.getRequestUri()));
                        httpResponse.setStatusCode(200);
                        httpResponse.setReasonPhrase("OK");
                        std::string ext = RequestUtils::getFileExtension(path.back());
                        std::string contentType = "";
                        if (ext == ".js") {
                            contentType = "text/javascript; charset=utf-8";
                        } else if (ext == ".html") {
                            contentType = "text/html; charset=utf-8";
                        } else if (ext == ".css") {
                            contentType = "text/css; charset=utf-8";
                        }
                        httpResponse.addResponseHeader("Access-Control-Allow-Origin", "*");
                        httpResponse.addResponseHeader("Connection", "keep-alive");
                        httpResponse.addEntityHeader("Content-Type", contentType);
                        //httpResponse.addEntityHeader("Content-Encoding", "gzip");

                    } catch (...) {
                       // throw HTTPException("File not found");
                        httpResponse = defaultResponse;
                    }
                } else {
                    //throw HTTPException("Bad requestUri");
                    httpResponse = defaultResponse;
                }
            }
            return httpResponse;
        };

        std::function<HTTPResponse(HTTPRequest &)> onPost = [] (HTTPRequest &request) -> HTTPResponse {
            HTTPResponse httpResponse;
            httpResponse.setHttpVersion("HTTP/1.1");

            std::vector<std::string> path = RequestUtils::parseRequestUri(request.getRequestUri());
            if (path.size() == 1 && path.back() == "users") {
                chat.addUser(RequestUtils::getValueFromJsonByKey(request.getMessageBody(), "user"));
                httpResponse.setStatusCode(200);
                httpResponse.setReasonPhrase("OK");
                httpResponse.addEntityHeader("Content-Type", "text/plain; charset=UTF-8");
                httpResponse.setMessageBody("User added\r\n");
            } else if (path.size() == 1 && path.back() == "messages") {
                const std::string &messageBody = request.getMessageBody();
                if (messageBody[0] != '{' || messageBody[messageBody.length() - 1] != '}' && messageBody[messageBody.length() - 2] != '}') {
                    throw NotFullRequestException("Json expected");
                }
                chat.addMessage(Message(
                        RequestUtils::getValueFromJsonByKey(messageBody, "user"),
                        RequestUtils::getValueFromJsonByKey(messageBody, "message"))
                );
                httpResponse.setStatusCode(200);
                httpResponse.setReasonPhrase("OK");
                httpResponse.addEntityHeader("Content-Type", "text/plain; charset=UTF-8");
                httpResponse.addResponseHeader("Access-Control-Allow-Origin", "*");
                httpResponse.setMessageBody("Message added\r\n");
            } else {
                throw HTTPException("Bad requestUri");
            }
            return httpResponse;
        };

        HTTPServer server = HTTPServer("0.0.0.0", "2323", 10, onGet, onPost, IOLoop);

        IOLoop.run();
    } catch (TCPException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (EpollException& e) {
        std::cerr << e.getMessage() << "\n";
    } catch (char const *s) {
        std::cerr << s << "\n";
    } catch (...) {
    }

    std::cout << "Finish\n";
    return 0;
}
