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

#ifndef SERVER_H
#define SERVER_H

//standard library includes
#include <atomic>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

#include "application/AudioLibrary.h"
#include "util/threading/ThreadPool.h"
#include "ServerSocket.h"
#include "Socket.h"

/**
 * Class encapsulating functionality for the server.
 */
class Server {

    ServerSocket serverSocket;
   
    unsigned maxConnections;

    std::atomic_bool running;

    ThreadPool threadPool;

    protected:

    std::mutex stdoutMutex, stderrMutex;

    public:

    /**
     * Constructor. Initializes the server by binding the
     * port passed as a parameter.
     *
     * @param port
     *        Port that the server listens to for incoming connections.
     *
     * @param maxConnections 
     *        Maximum connections the server can accept simultaneously.
     *
     * @param servingThreads
     *        How many threads the server will spawn.
     */
    Server(unsigned short port, unsigned maxConnections, unsigned servingThreads);

    /**
     * Destructor.
     */
    virtual ~Server();

    /**
     * Disable copy constructor.
     */
    Server(const Server& copy) = delete;

    /**
     * Disable assignment.
     */
    Server& operator=(const Server& other) = delete;

    /**
     * Runs the server.
     */
    void Run();

    /**
     * Stops the server from running.
     */
    void Stop();

    protected:
    
    /**
     * Code that serves the client goes here
     */
    virtual void Serve(Socket& clientSocket) = 0;

    private: 

    /**
     * Serves a client.
     *
     * @param clientSocket
     *        Client's socket.
     */
    void ServeClient(Socket& clientSocket);
};

#endif