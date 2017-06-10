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

#ifndef IHTTP_REQUEST_EXTRACTOR
#define IHTTP_REQUEST_EXTRACTOR

//standard library includes
#include <string>


#include "HttpException.h"

class HttpRequest;

/**
 * Interface for classes that knows how to extract data from
 * an HTTP request.
 */
class IHttpRequestExtractor {

    public:

    class HttpExtractionException : public HttpException {

        public:

        HttpExtractionException(const std::string& message) : HttpException(message) {};

        virtual ~HttpExtractionException() noexcept {};
    };

    virtual ~IHttpRequestExtractor() {};

    virtual std::string ExtractGET(const HttpRequest& request) const = 0;	

    virtual std::string ExtractHOST(const HttpRequest& request) const = 0;
};

#endif