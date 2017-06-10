/**
 * Copyright (c) 2011-2017, Vasileios Daras. All rights reserved.
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

#include "Server.h"

//standard library includes
#include <iostream>
#include <future>

#include "system/SystemException.h"

Server::Server(unsigned short port, unsigned maxConnections, unsigned servingThreads)
: serverSocket(port),
  maxConnections(maxConnections),
  running(false),
  threadPool(servingThreads) {

    serverSocket.Open();

}


Server::~Server() {
}


void Server::Run() {

    serverSocket.Listen(maxConnections);
    std::cout << "Server now listening for incoming connections at port " << serverSocket.GetPort() << '\n';

    threadPool.Startup();

    running = true;
    while(running) {
    
        if(serverSocket.IsReady()) {

            try {
                
                auto clientSocketPtr = std::make_shared<Socket>(serverSocket.Accept());

                threadPool.EnqueueTask([this, clientSocketPtr]() mutable {
                    clientSocketPtr->SetReceiveTimeout(1);
                    clientSocketPtr->SetSendTimeout(1);
                    this->ServeClient(*clientSocketPtr);
                });

            } catch(const SystemException& e) {
                std::lock_guard<std::mutex> guard(stderrMutex);
                std::cerr << e.what() << '\n';
            }

        }
    }
}


void Server::Stop() {
    running = false;
}


void Server::ServeClient(Socket& clientSocket) {
 
    try {

        {
            std::lock_guard<std::mutex> guard(stdoutMutex);
            std::cout << "Serving new client...\n";
        }
    
        Serve(clientSocket);

        {
            std::lock_guard<std::mutex> guard(stdoutMutex);
            std::cout << "Client served..\n";
        }

    } catch(const std::exception& e) {
        std::lock_guard<std::mutex> guard(stderrMutex);
        std::cerr << e.what() << '\n';
    } catch(...) {
        std::lock_guard<std::mutex> guard(stderrMutex);
        std::cerr << "Unexpected error!\n";
    }
    clientSocket.Close();
}
