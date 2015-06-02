cmake_minimum_required(VERSION 3.2)
project(ChatCPP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES server/main.cpp)
add_executable(ChatCPP ${SOURCE_FILES} epollhandler.h epollhandler.cpp handler.cpp handler.h tcpconnection.cpp tcpconnection.h tcpexception.h tcpsocket.cpp tcpsocket.h server/server.cpp server/server.h)