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

#if defined __unix__ || (defined (__APPLE__) && defined (__MACH__))
#ifndef BSD_SOCKET_H
#define BSD_SOCKET_H 

//systems includes
#include <sys/socket.h>

//standard library includes
#include <array>
#include <cstring>
#include <iostream>

#include "system/network/NetworkException.h"

/**
 * Class encapsulating functiality for a TCP Berkeley socket.
 */
class BSDSocket {

    bool opened;

    int descriptor;

    public:

    /**
     * Constructor.
     *
     * @param open
     *        Whether to open the port during construction or not
     *
     * @throws NetworkException 
     *         If the port can't be opened.
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
     * Move constructor.
     */
    BSDSocket(BSDSocket&& rvalue); 

    /**
     * Destructor.
     */
    ~BSDSocket();

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
    void Open();

    /**
     * Closes the socket.
     */
    void Close();

    /**
     * Sends data to the socket.
     *
     * @param buffer 
     *        Data buffer.
     *
     */
    template<size_t n>
    void Send(const std::array<char, n>& buffer, size_t toSend = n) const;

    /**
     * Receives data from the socket.
     *
     * @param buffer 
     *        Data buffer.
     *
     * @return
     *        How much data was actually read.
     */
    template<size_t n>
    size_t Receive(std::array<char, n>& buffer, size_t readSize = n) const;

    /**
     * Set most seconds to wait when receiving from this socket.
     *
     * @param seconds
     *        Timeout in seconds.
     */
    void SetReceiveTimeout(unsigned seconds);

    /**
     * Set most seconds to wait when sending using this socket.
     *
     * @param seconds
     *        Timeout in seconds.
     */
    void SetSendTimeout(unsigned seconds);

    /**
     * @return
     *         The file descriptor of the socket.
     */
    int GetDescriptor() const;    
};

template<size_t n>
void BSDSocket::Send(const std::array<char, n>& buffer, size_t toSend) const {

    const char* bufferPtr = buffer.data();
    toSend                = std::min(toSend, n);

    while(toSend > 0) {
        auto totalSent = send(descriptor, bufferPtr, toSend, 0);
        if(totalSent == -1) {
            throw NetworkException(strerror(errno));
        }

        bufferPtr += totalSent;
        toSend -= totalSent;
    }
}

template<size_t n>
size_t BSDSocket::Receive(std::array<char, n>& buffer, size_t readSize) const {
    auto read = recv(descriptor, buffer.data(), std::min(n, readSize), 0);
    if(read == -1) {
        throw NetworkException(strerror(errno));
    }
    return static_cast<size_t>(read);
}

#endif
#endif
