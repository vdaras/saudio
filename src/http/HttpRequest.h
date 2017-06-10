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

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "Http.h"

class HttpRequest {

    std::string request;

    public:

    /**
     * Constructor.
     *
     * @param data
     *        Raw data buffer containing the http request.
     *
     * @param dataSize
     *        How big is the data buffer
     */
    HttpRequest(char data[], unsigned dataSize);

    /**
     * Destructor.
     */
    ~HttpRequest();
 
    /**
     * @return
     *         The full HTTP message.
     */
    const std::string& GetMessage() const;
};

#endif