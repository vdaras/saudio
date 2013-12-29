/**
 * Copyright (c) 2011-2014, Vasileios Daras. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 */

//standard library includes
#include <csignal>
#include <exception>
#include <iostream>
#include <map>
#include <memory>

#include "application/AudioStreamingServer.h"
#include "application/exception/ArgumentException.h"
#include "system/SignalHandler.h"
#include "system/SystemException.h"
#include "system/network/NetworkException.h"

extern "C" {
#include "system/pgetopt.h"
}

const int DEFAULT_MAX_CONNECTIONS = 20;

/**
 * Prints program's usage help message.
 */
void PrintUsage() {
    std::cout << "USAGE: saudio -p port -l library_dir [-c max_connections][-t working_threads]\n"
    "-p              Port number the server listens to\n"
    "-l              Root directory of the server's music library\n"
    "-c              Maximum connections accepted by the server\n"
    "-t              Maximum working threads\n";
}

/**
 * Creates the server object.
 *
 * @return
 *         A Server object created by parsing options from command line arguments.
 */
std::unique_ptr<Server> CreateServer(int argc, char* argv[]) {
    char option;
    std::map<char, std::string> argValues;
    //put all argument values in a map
    while((option = pgetopt(argc, argv, "p:l:c:t:")) != -1) {
        if(poptarg != nullptr) {
            argValues[option] = poptarg;
        }
    }

    try {

        //get supplied values for port number and music library's root dir
        //if either is not supplied then throw an exception since they
        //are mandatory
        unsigned short portNo;

        std::string libraryDirectory;
      
        if(argValues.find('p') != argValues.end() &&
            argValues.find('l') != argValues.end()) {

            portNo = std::stoi(argValues['p']);

            libraryDirectory = std::string(argValues['l']);
            if(libraryDirectory[libraryDirectory.length() - 1] != '/') {
                libraryDirectory += '/';
            }

        } else {
            throw InsufficientArgumentsException();
        }

        //get max connections if supplied, else use default value
        unsigned maxConnections = argValues.find('c') != argValues.end() ?
                                  std::stoi(argValues['c']) :
                                  DEFAULT_MAX_CONNECTIONS;
        
        unsigned servingThreads = argValues.find('t') != argValues.end() ?
                                  std::stoi(argValues['t']) :
                                  maxConnections;
        
        return std::unique_ptr<Server>(new AudioStreamingServer(portNo, maxConnections, servingThreads, libraryDirectory));

    } catch(const std::invalid_argument& e) {
        throw InvalidArgumentException("c", argValues['c']);
    } catch(const std::system_error& e) {
        throw SystemException(e.what());
    }
}

int main(int argc, char* argv[]) {
    std::unique_ptr<Server> server;
    try {
        server = CreateServer(argc, argv);
    } catch(const ArgumentException& e) {
        std::cout << e.what() << "\n\n";
        PrintUsage();
        return -1;
    } catch(const SystemException& e) {
        std::cout << e.what() << '\n';
        return -1;
    }

    //install signal handlers
    signal(SIGINT, &InvokeSignalHandlers);
    signal(EINTR, &InvokeSignalHandlers);
    
    //ignore signal when client gets disconnected in a thread
    signal(SIGPIPE, SIG_IGN);
    auto stopServerCallback = [&](int signal) {
        server->Stop();
    };

    //stop the server gracefully if a SIGINT or EINTR is received
    AddSignalHandler(SIGINT, stopServerCallback);
    AddSignalHandler(EINTR, stopServerCallback);

    try {
        server->Run();
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        return -1;
    }
    return 0;
}
