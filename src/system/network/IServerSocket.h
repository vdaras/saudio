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

#ifndef ISERVER_SOCKET_H
#define ISERVER_SOCKET_H

#include "ISocket.h"

//standard library includes
#include <memory>

/**
 * Interface to be implemented for server socket functionality.
 */
class IServerSocket : public virtual ISocket {

    public:

    /**
.    * Destructor
     */
    virtual ~IServerSocket() {};

    /**
     * Start listening on this port for incoming connections.
     */
    virtual void Listen(int maxConnections) = 0;

    /**
     * @return
     *          Whether the server socket is ready to accept
     *          a connection or not.
     */
    virtual bool IsReady() const = 0;

    /**
     * Accepts an incoming connection.
     *
     * @return 
     *          Client's socket
     */
    virtual std::shared_ptr<ISocket> Accept() const = 0;

    /**
     * @return
     *          The port the server socket is listening to.
     *
     */
    virtual unsigned short GetPort() const = 0;  
};

#endif