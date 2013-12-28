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

#include "ParsingHttpRequestExtractor.h"

#include "HttpRequest.h"

std::string ParsingHttpRequestExtractor::ExtractGET(const HttpRequest& request) const
{

    const std::string& message = request.GetMessage();

    size_t methodStart = message.find("GET");
    if(methodStart == std::string::npos)
    {
        throw HttpExtractionException("No GET line in HTTP request.");
    }

    size_t methodEnd = message.find("\r\n", methodStart);
    if(methodEnd == std::string::npos)
    {
        throw HttpExtractionException("GET line doesn't end with carriage return in HTTP request.");
    }

    size_t requestPathStart = message.find_first_not_of(' ', methodStart + 3);
    if(requestPathStart == std::string::npos)
    {
        throw HttpExtractionException("Malformed GET line.");
    }

    size_t requestPathEnd = message.find_first_of(' ', requestPathStart);
    if(requestPathEnd == std::string::npos)
    {
        throw HttpExtractionException("Malformed GET line.");
    }

    return message.substr(requestPathStart, requestPathEnd - requestPathStart);
}



std::string ParsingHttpRequestExtractor::ExtractHOST(const HttpRequest& request) const
{

    const std::string& message = request.GetMessage();

    size_t hostStart = message.find("Host:");
    if(hostStart == std::string::npos)
    {
        throw HttpExtractionException("No Host line in HTTP request.");
    }

    size_t hostEnd = message.find("\r\n", hostStart);
    if(hostEnd == std::string::npos)
    {
        throw HttpExtractionException("Host line doesn't end with carriage return in HTTP request.");
    }

    size_t hostNameStart = message.find_first_not_of(' ', hostStart + 5);
    if(hostNameStart == std::string::npos)
    {
        throw HttpExtractionException("Malformed Host line");
    }

    return message.substr(hostNameStart, hostEnd - hostNameStart);
}
