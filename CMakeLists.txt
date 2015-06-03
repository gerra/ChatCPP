cmake_minimum_required(VERSION 2.8)
project(ChatCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES HTTPServer/main.cpp)
add_executable(ChatCPP ${SOURCE_FILES} epollhandler.h epollhandler.cpp handler.cpp handler.h tcpconnection.cpp tcpconnection.h tcpexception.h tcpsocket.cpp tcpsocket.h TCPServer/TCPServer.cpp TCPServer/TCPServer.h HTTPServer/HTTPServer.cpp HTTPServer/HTTPServer.h HTTPServer/RequestUtils.cpp HTTPServer/RequestUtils.h)