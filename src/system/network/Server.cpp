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

#include "Server.h"

//standard library includes
#include <iostream>

//system includes
#include <unistd.h>

#include "ServerSocketFactory.h"
#include "system/SystemException.h"
#include "util/scopeguard/SimpleScopeGuard.h"

Server::Server(unsigned short port, unsigned maxConnections, unsigned servingThreads)
: serverSocket(ServerSocketFactory::CreateServerSocket(port)),
  maxConnections(maxConnections),
  running(false),
  threadPool(servingThreads) { 

    serverSocket->Open();

}


Server::~Server() {
}


void Server::Run() {

    serverSocket->Listen(maxConnections);

    std::cout << "Server now listening for incoming connections at port " << serverSocket->GetPort() << '\n';

    running = true;

    while(running) {
        
        if(serverSocket->IsReady()) {

            try {

                std::shared_ptr<ISocket> clientSocket = serverSocket->Accept();

                //stop receiving if 5 seconds pass and client doesn't send data
                clientSocket->SetReceiveTimeout(5);
			
                threadPool.EnqueueTask([=]() {
                    this->ServeClient(clientSocket);
                });

            } catch(const SystemException& e) {
                
                std::lock_guard<std::mutex> guard(stderrMutex);
                std::cerr << e.what() << '\n';
 
            } catch(const std::system_error& e) {

                std::lock_guard<std::mutex> guard(stderrMutex);
                std::cerr << "Could not start thread: " << e.what() << '\n';
            }
        }
    }
}

void Server::Stop() {
	running = false;
}

void Server::ServeClient(std::shared_ptr<ISocket> clientSocket) {

    try {

        Serve(clientSocket);

    } catch (const std::exception& e) {

        std::lock_guard<std::mutex> guard(stderrMutex);
        std::cerr << e.what();
    }

    clientSocket->Close();
}
