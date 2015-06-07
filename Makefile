# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/german/CPP/ChatCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/german/CPP/ChatCPP

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/german/CPP/ChatCPP/CMakeFiles /home/german/CPP/ChatCPP/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/german/CPP/ChatCPP/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ChatCPP

# Build rule for target.
ChatCPP: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ChatCPP
.PHONY : ChatCPP

# fast build rule for target.
ChatCPP/fast:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/build
.PHONY : ChatCPP/fast

Chat/Chat.o: Chat/Chat.cpp.o
.PHONY : Chat/Chat.o

# target to build an object file
Chat/Chat.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/Chat/Chat.cpp.o
.PHONY : Chat/Chat.cpp.o

Chat/Chat.i: Chat/Chat.cpp.i
.PHONY : Chat/Chat.i

# target to preprocess a source file
Chat/Chat.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/Chat/Chat.cpp.i
.PHONY : Chat/Chat.cpp.i

Chat/Chat.s: Chat/Chat.cpp.s
.PHONY : Chat/Chat.s

# target to generate assembly for a file
Chat/Chat.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/Chat/Chat.cpp.s
.PHONY : Chat/Chat.cpp.s

Chat/User.o: Chat/User.cpp.o
.PHONY : Chat/User.o

# target to build an object file
Chat/User.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/Chat/User.cpp.o
.PHONY : Chat/User.cpp.o

Chat/User.i: Chat/User.cpp.i
.PHONY : Chat/User.i

# target to preprocess a source file
Chat/User.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/Chat/User.cpp.i
.PHONY : Chat/User.cpp.i

Chat/User.s: Chat/User.cpp.s
.PHONY : Chat/User.s

# target to generate assembly for a file
Chat/User.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/Chat/User.cpp.s
.PHONY : Chat/User.cpp.s

HTTPServer/HTTPServer.o: HTTPServer/HTTPServer.cpp.o
.PHONY : HTTPServer/HTTPServer.o

# target to build an object file
HTTPServer/HTTPServer.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/HTTPServer.cpp.o
.PHONY : HTTPServer/HTTPServer.cpp.o

HTTPServer/HTTPServer.i: HTTPServer/HTTPServer.cpp.i
.PHONY : HTTPServer/HTTPServer.i

# target to preprocess a source file
HTTPServer/HTTPServer.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/HTTPServer.cpp.i
.PHONY : HTTPServer/HTTPServer.cpp.i

HTTPServer/HTTPServer.s: HTTPServer/HTTPServer.cpp.s
.PHONY : HTTPServer/HTTPServer.s

# target to generate assembly for a file
HTTPServer/HTTPServer.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/HTTPServer.cpp.s
.PHONY : HTTPServer/HTTPServer.cpp.s

HTTPServer/RequestUtils.o: HTTPServer/RequestUtils.cpp.o
.PHONY : HTTPServer/RequestUtils.o

# target to build an object file
HTTPServer/RequestUtils.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/RequestUtils.cpp.o
.PHONY : HTTPServer/RequestUtils.cpp.o

HTTPServer/RequestUtils.i: HTTPServer/RequestUtils.cpp.i
.PHONY : HTTPServer/RequestUtils.i

# target to preprocess a source file
HTTPServer/RequestUtils.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/RequestUtils.cpp.i
.PHONY : HTTPServer/RequestUtils.cpp.i

HTTPServer/RequestUtils.s: HTTPServer/RequestUtils.cpp.s
.PHONY : HTTPServer/RequestUtils.s

# target to generate assembly for a file
HTTPServer/RequestUtils.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/RequestUtils.cpp.s
.PHONY : HTTPServer/RequestUtils.cpp.s

HTTPServer/main.o: HTTPServer/main.cpp.o
.PHONY : HTTPServer/main.o

# target to build an object file
HTTPServer/main.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/main.cpp.o
.PHONY : HTTPServer/main.cpp.o

HTTPServer/main.i: HTTPServer/main.cpp.i
.PHONY : HTTPServer/main.i

# target to preprocess a source file
HTTPServer/main.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/main.cpp.i
.PHONY : HTTPServer/main.cpp.i

HTTPServer/main.s: HTTPServer/main.cpp.s
.PHONY : HTTPServer/main.s

# target to generate assembly for a file
HTTPServer/main.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/HTTPServer/main.cpp.s
.PHONY : HTTPServer/main.cpp.s

TCPServer/TCPServer.o: TCPServer/TCPServer.cpp.o
.PHONY : TCPServer/TCPServer.o

# target to build an object file
TCPServer/TCPServer.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/TCPServer/TCPServer.cpp.o
.PHONY : TCPServer/TCPServer.cpp.o

TCPServer/TCPServer.i: TCPServer/TCPServer.cpp.i
.PHONY : TCPServer/TCPServer.i

# target to preprocess a source file
TCPServer/TCPServer.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/TCPServer/TCPServer.cpp.i
.PHONY : TCPServer/TCPServer.cpp.i

TCPServer/TCPServer.s: TCPServer/TCPServer.cpp.s
.PHONY : TCPServer/TCPServer.s

# target to generate assembly for a file
TCPServer/TCPServer.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/TCPServer/TCPServer.cpp.s
.PHONY : TCPServer/TCPServer.cpp.s

model/HTTPRequest.o: model/HTTPRequest.cpp.o
.PHONY : model/HTTPRequest.o

# target to build an object file
model/HTTPRequest.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/HTTPRequest.cpp.o
.PHONY : model/HTTPRequest.cpp.o

model/HTTPRequest.i: model/HTTPRequest.cpp.i
.PHONY : model/HTTPRequest.i

# target to preprocess a source file
model/HTTPRequest.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/HTTPRequest.cpp.i
.PHONY : model/HTTPRequest.cpp.i

model/HTTPRequest.s: model/HTTPRequest.cpp.s
.PHONY : model/HTTPRequest.s

# target to generate assembly for a file
model/HTTPRequest.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/HTTPRequest.cpp.s
.PHONY : model/HTTPRequest.cpp.s

model/HTTPResponse.o: model/HTTPResponse.cpp.o
.PHONY : model/HTTPResponse.o

# target to build an object file
model/HTTPResponse.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/HTTPResponse.cpp.o
.PHONY : model/HTTPResponse.cpp.o

model/HTTPResponse.i: model/HTTPResponse.cpp.i
.PHONY : model/HTTPResponse.i

# target to preprocess a source file
model/HTTPResponse.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/HTTPResponse.cpp.i
.PHONY : model/HTTPResponse.cpp.i

model/HTTPResponse.s: model/HTTPResponse.cpp.s
.PHONY : model/HTTPResponse.s

# target to generate assembly for a file
model/HTTPResponse.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/HTTPResponse.cpp.s
.PHONY : model/HTTPResponse.cpp.s

model/epollhandler.o: model/epollhandler.cpp.o
.PHONY : model/epollhandler.o

# target to build an object file
model/epollhandler.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/epollhandler.cpp.o
.PHONY : model/epollhandler.cpp.o

model/epollhandler.i: model/epollhandler.cpp.i
.PHONY : model/epollhandler.i

# target to preprocess a source file
model/epollhandler.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/epollhandler.cpp.i
.PHONY : model/epollhandler.cpp.i

model/epollhandler.s: model/epollhandler.cpp.s
.PHONY : model/epollhandler.s

# target to generate assembly for a file
model/epollhandler.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/epollhandler.cpp.s
.PHONY : model/epollhandler.cpp.s

model/handler.o: model/handler.cpp.o
.PHONY : model/handler.o

# target to build an object file
model/handler.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/handler.cpp.o
.PHONY : model/handler.cpp.o

model/handler.i: model/handler.cpp.i
.PHONY : model/handler.i

# target to preprocess a source file
model/handler.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/handler.cpp.i
.PHONY : model/handler.cpp.i

model/handler.s: model/handler.cpp.s
.PHONY : model/handler.s

# target to generate assembly for a file
model/handler.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/handler.cpp.s
.PHONY : model/handler.cpp.s

model/tcpsocket.o: model/tcpsocket.cpp.o
.PHONY : model/tcpsocket.o

# target to build an object file
model/tcpsocket.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/tcpsocket.cpp.o
.PHONY : model/tcpsocket.cpp.o

model/tcpsocket.i: model/tcpsocket.cpp.i
.PHONY : model/tcpsocket.i

# target to preprocess a source file
model/tcpsocket.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/tcpsocket.cpp.i
.PHONY : model/tcpsocket.cpp.i

model/tcpsocket.s: model/tcpsocket.cpp.s
.PHONY : model/tcpsocket.s

# target to generate assembly for a file
model/tcpsocket.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/model/tcpsocket.cpp.s
.PHONY : model/tcpsocket.cpp.s

tcpconnection.o: tcpconnection.cpp.o
.PHONY : tcpconnection.o

# target to build an object file
tcpconnection.cpp.o:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/tcpconnection.cpp.o
.PHONY : tcpconnection.cpp.o

tcpconnection.i: tcpconnection.cpp.i
.PHONY : tcpconnection.i

# target to preprocess a source file
tcpconnection.cpp.i:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/tcpconnection.cpp.i
.PHONY : tcpconnection.cpp.i

tcpconnection.s: tcpconnection.cpp.s
.PHONY : tcpconnection.s

# target to generate assembly for a file
tcpconnection.cpp.s:
	$(MAKE) -f CMakeFiles/ChatCPP.dir/build.make CMakeFiles/ChatCPP.dir/tcpconnection.cpp.s
.PHONY : tcpconnection.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... ChatCPP"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Chat/Chat.o"
	@echo "... Chat/Chat.i"
	@echo "... Chat/Chat.s"
	@echo "... Chat/User.o"
	@echo "... Chat/User.i"
	@echo "... Chat/User.s"
	@echo "... HTTPServer/HTTPServer.o"
	@echo "... HTTPServer/HTTPServer.i"
	@echo "... HTTPServer/HTTPServer.s"
	@echo "... HTTPServer/RequestUtils.o"
	@echo "... HTTPServer/RequestUtils.i"
	@echo "... HTTPServer/RequestUtils.s"
	@echo "... HTTPServer/main.o"
	@echo "... HTTPServer/main.i"
	@echo "... HTTPServer/main.s"
	@echo "... TCPServer/TCPServer.o"
	@echo "... TCPServer/TCPServer.i"
	@echo "... TCPServer/TCPServer.s"
	@echo "... model/HTTPRequest.o"
	@echo "... model/HTTPRequest.i"
	@echo "... model/HTTPRequest.s"
	@echo "... model/HTTPResponse.o"
	@echo "... model/HTTPResponse.i"
	@echo "... model/HTTPResponse.s"
	@echo "... model/epollhandler.o"
	@echo "... model/epollhandler.i"
	@echo "... model/epollhandler.s"
	@echo "... model/handler.o"
	@echo "... model/handler.i"
	@echo "... model/handler.s"
	@echo "... model/tcpsocket.o"
	@echo "... model/tcpsocket.i"
	@echo "... model/tcpsocket.s"
	@echo "... tcpconnection.o"
	@echo "... tcpconnection.i"
	@echo "... tcpconnection.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
