cmake_minimum_required(VERSION 2.8)
project(ChatCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES HTTPServer/main.cpp)
add_executable(ChatCPP ${SOURCE_FILES} model/epollhandler.h model/epollhandler.cpp model/handler.cpp model/handler.h tcpconnection.cpp tcpconnection.h model/tcpexception.h model/tcpsocket.cpp model/tcpsocket.h TCPServer/TCPServer.cpp TCPServer/TCPServer.h HTTPServer/HTTPServer.cpp HTTPServer/HTTPServer.h HTTPServer/RequestUtils.cpp HTTPServer/RequestUtils.h model/HTTPRequest.cpp model/HTTPRequest.h model/HTTPResponse.cpp model/HTTPResponse.h model/HTTPException.h Chat/Chat.cpp Chat/Chat.h Chat/Message.h model/SignalHandler.cpp model/SignalHandler.h)