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

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "Http.h"

//standard library includes
#include <string>


/**
 * Class representing an HTTP response.
 */
class HttpResponse {
    
    HttpVersion version;

    HttpResponseCode code;

    HttpContentType contentType;

    unsigned contentLength;

    std::string attachmentName;

    public:

    /**
     * Constructor.
     *
     * @param version
     *        Version of the HTTP used.
     *
     * @param code
     *        Response's HTTP code.
     *
     * @param contentType 
     *        Response's HTTP content type.
     *
     * @parma contentLength
     *        Response's length in bytes.
     */
    HttpResponse(HttpVersion version, HttpResponseCode code, HttpContentType contentType, unsigned contentLength);


    /**
     * Constructor.
     *
     * @param version
     *        Version of the HTTP used.
     *
     * @param code
     *        Response's HTTP code.
     *
     * @param contentType 
     *        Response's HTTP content type.
     *
     * @parma contentLength
     *        Response's length in bytes.
     */
    HttpResponse(HttpVersion version, HttpResponseCode code, HttpContentType contentType, unsigned contentLength, const std::string& attachmentName);


    /**
     * Destructor.
     */
    ~HttpResponse();


    /**
     * Generates the HTTP response header.
     */
    std::string GenerateHeader() const;
};

#endif