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
#ifndef BSD_SOCKET_H
#define BSD_SOCKET_H 

//systems includes
#include <sys/socket.h>

//standard library includes
#include <array>
#include <cstring>
#include <iostream>

#include "system/network/ISocket.h"

/**
 * Class encapsulating functiality for a TCP Berkeley socket.
 */
class BSDSocket : public virtual ISocket {

    bool opened;

    int descriptor;

    public:

    /**
     * Constructor.
     *
     * @param open
     *        Whether to open the port during construction or not
     *
     * @throws
     *        AudioStreamer Exception
     *        If the port can't be opened
     */
    explicit BSDSocket(bool open = false);


    /**
     * Constructs a Socket object using a descriptor.
     *
     * @param descriptor
     *        Socket's descriptor.
     */
    explicit BSDSocket(int descriptor);


    /**
     * Destructor.
     */
    virtual ~BSDSocket();

    /**
     * Move constructor.
     */
    BSDSocket(BSDSocket&& rvalue); 

    /**
     * Move assignment operator.
     */
    BSDSocket& operator=(BSDSocket&& rvalue);

    /**
     * Disable copy construction.
     */
    BSDSocket(const BSDSocket& copy) = delete;

    /**
     * Disable assignment.
     */
    BSDSocket& operator=(const BSDSocket& other) = delete;

    /**
     * Opens the socket.
     */
    virtual void Open() override;

    /**
     * Closes the socket.
     */
    virtual void Close() override;

    /**
     * Sends data to the socket.
     *
     * @param buffer 
     *        Data buffer.
     *
     * @param n 
     *        How many of the data to send.
     */
    virtual void Send(const char buffer[], unsigned n) const override;

    /**
     * Receives data from the socket.
     *
     *
     * @param buffer 
     *        Data buffer.
     *
     * @param n 
     *        How much data to read.
     *
     * @return
     *        How much data was actually read.
     */
    virtual unsigned Receive(char buffer[], unsigned n) const override;

    /**
     * Set most seconds to wait when receiving from this socket.
     *
     * @param seconds
     *        Timeout in seconds.
     */
    virtual void SetReceiveTimeout(unsigned seconds) override;

    protected:

    /**
     * @return
     *         The file descriptor of the socket.
     */
    const int GetDescriptor() const;    
};

#endif
#endif
