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

#ifndef ISOCKET_H
#define ISOCKET_H

/**
 * Interface to be implemented for socket functionality.
 */
class ISocket {

    public:

    /**
     * Destructor.
     */
    virtual ~ISocket() {};

    /**
     * Opens the socket.
     *
     * @throws
     *        OpenSocketException If the socket cannot be opened.
     */
    virtual void Open() = 0;

    /**
     * Closes the socket.
     */
    virtual void Close() = 0;

    /**
     * Sends data to the socket.
     *
     *
     * @param buffer 
     *        Data buffer.
     *
     * @param n 
     *        How many of the data to send.
     */
    virtual void Send(const char buffer[], unsigned n) const = 0;

    /**
     * Receives data from the socket.
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
    virtual unsigned Receive(char buffer[], unsigned n) const = 0;


    /**
     * Set most seconds to wait when receiving from this socket.
     *
     * @param seconds
     *        Timeout in seconds.
     */
    virtual void SetReceiveTimeout(unsigned seconds) = 0;
};

#endif
