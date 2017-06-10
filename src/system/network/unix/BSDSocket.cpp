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
#include "BSDSocket.h"

//system includes
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>

//standard library includes
#include <string>

BSDSocket::BSDSocket(bool open)
: opened(false),
  descriptor(-1) {
    if(open) {
        Open();
    }
}

BSDSocket::BSDSocket(int descriptor)
: opened(true),
  descriptor(descriptor) {
}

BSDSocket::BSDSocket(BSDSocket&& rvalue)
: opened(rvalue.opened),
descriptor(rvalue.descriptor) {
    rvalue.opened = false;
    rvalue.descriptor = -1;
}

BSDSocket::~BSDSocket() {
    Close();
}

BSDSocket& BSDSocket::operator=(BSDSocket&& rvalue) {
    opened = rvalue.opened;
    descriptor = rvalue.descriptor;
    rvalue.opened = false;
    rvalue.descriptor = -1;
    return *this;
}


void BSDSocket::Open() {
    if(!opened) {
        descriptor = socket(AF_INET, SOCK_STREAM, 0);
        if(descriptor == -1) {
            throw NetworkException(strerror(errno));
        }
        opened = true;
    }
}


void BSDSocket::Close() {
    if(opened) {
        close(descriptor);
        opened = false;
    }
}


int BSDSocket::GetDescriptor() const {
    return descriptor;
}


void BSDSocket::SetReceiveTimeout(unsigned seconds) {
    timeval t;
    t.tv_sec = seconds;
    t.tv_usec = 0;
    auto ret = setsockopt(descriptor, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&t),sizeof(struct timeval));
    if(ret == -1) {
        throw NetworkException(strerror(errno));
    }
}


void BSDSocket::SetSendTimeout(unsigned seconds) {
    timeval t;
    t.tv_sec = seconds;
    t.tv_usec = 0;
    auto ret = setsockopt(descriptor, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&t),sizeof(struct timeval));
    if(ret == -1) {
        throw NetworkException(strerror(errno));
    }
}

#endif
