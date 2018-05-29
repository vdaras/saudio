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
#include "BSDServerSocket.h"

//system includes
#include <netdb.h>
#include <csignal>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

//standard library includes
#include <string>

#include "system/network/NetworkException.h"

BSDServerSocket::BSDServerSocket(unsigned short portNo, bool open)
: BSDSocket(open),
  portNo(portNo),
  listening(false) {
    FD_ZERO(&masterDescriptors);
}


BSDServerSocket::~BSDServerSocket() {
}


BSDServerSocket::BSDServerSocket(BSDServerSocket&& rvalue)
: BSDSocket(std::move(rvalue)),
  portNo(rvalue.portNo),
  listening(rvalue.listening),
  masterDescriptors(rvalue.masterDescriptors) {
    rvalue.portNo = 0;
    rvalue.listening = false;
}


BSDServerSocket& BSDServerSocket::operator=(BSDServerSocket&& rvalue) {
    BSDSocket::operator=(std::move(rvalue));
    portNo = rvalue.portNo;
    listening = rvalue.listening;
    masterDescriptors = rvalue.masterDescriptors;
    rvalue.portNo = 0;
    rvalue.listening = false;
    return *this;
}


void BSDServerSocket::Open() {

    BSDSocket::Open();
    int acceptDescriptor = GetDescriptor();
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(portNo);
    if(bind(acceptDescriptor, (sockaddr*) &serverAddress, sizeof(serverAddress)) == -1) {
        throw NetworkException(strerror(errno));
    }
    FD_SET(acceptDescriptor, &masterDescriptors);
}


void BSDServerSocket::Listen(int maxConnections) {

    if(listen(GetDescriptor(), maxConnections) != 0) {
        throw NetworkException(strerror(errno));
    }
    listening = true;
}


bool BSDServerSocket::IsReady() const {
    int acceptDescriptor = GetDescriptor();
    int maxFd = acceptDescriptor + 1;
    fd_set readDescriptors = masterDescriptors;
    if(select(maxFd, &readDescriptors, NULL, NULL, NULL) != -1) {
        for(int i = 0; i < maxFd; i++) {
            if(FD_ISSET(i, &readDescriptors)) {
                if(i == acceptDescriptor) {
                    return true;
                }
            }
        }
    }
    return false;
}


SocketTemplate<BSDSocket> BSDServerSocket::Accept() const {
    sockaddr_in clientAddress;
    socklen_t addressLength = sizeof(clientAddress);
    int descriptor = accept(GetDescriptor(), (sockaddr*) &clientAddress, &addressLength);
    if(descriptor == -1) {
        throw NetworkException(strerror(errno));
    }
    
    return SocketTemplate<BSDSocket>(descriptor);
}


unsigned short BSDServerSocket::GetPort() const {
    return portNo;
}

#endif
