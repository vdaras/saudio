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

#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
#ifndef BSD_SERVER_SOCKET_H
#define BSD_SERVER_SOCKET_H 

//system includes
#include <sys/select.h>

#include "BSDSocket.h"
#include "system/network/IServerSocket.h"


/**
 * Class encapsulating functiality for a TCP BSD server socket.
 */
class BSDServerSocket : public BSDSocket, public IServerSocket {

    unsigned short portNo;

    bool listening;

    fd_set masterDescriptors;
    
    public:

    /**
     * Constructor.
     *
     * @param portNo
     *        Port to listen to
     *
     * @param open
     *        Whether to open the port during construction or not
     *
     * @throws
     *        AudioStreamer Exception
     *        If the port can't be opened
     */
    BSDServerSocket(unsigned short portNo, bool open = false);

    /**
     * Destructor.
     */
    ~BSDServerSocket();

    /**
     * Move constructor.
     */
    BSDServerSocket(BSDServerSocket&& rvalue); 

    /**
     * Move assignment operator.
     */
    BSDServerSocket& operator=(BSDServerSocket&& rvalue);

    /**
     * Opens the server socket.
     *
     * @throws
     *        OpenSocketException If the port can't be opened.
     *        BindSocketException If the port can't be binded.
     */
    virtual void Open() override;

    /**
     * Start listening on this port for incoming connections.
     */
    virtual void Listen(int maxConnections) override;

    /**
     * @return
     *          Whether the server socket is ready to accept
     *          a connection or not.
     */
    virtual bool IsReady() const override;

    /**
     * Accepts an incoming connection.
     *
     * @return 
     *         Client's socket
     */
    virtual std::shared_ptr<ISocket> Accept() const override;

    /**
     * Returns the port the server socket is listening to.
     */
    virtual unsigned short GetPort() const override;


    /**
     * Disable copy construction.
     */
    BSDServerSocket(const BSDServerSocket& copy) = delete;

    /**
     * Disable assignment.
     */
    BSDServerSocket& operator=(const BSDServerSocket& other) = delete;

};

#endif
#endif