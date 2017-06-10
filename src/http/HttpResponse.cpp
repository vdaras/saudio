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

#include "HttpResponse.h"

//standard library includes
#include <sstream>

HttpResponse::HttpResponse(HttpVersion version, HttpResponseCode code, HttpContentType contentType, unsigned contentLength)
: version(version),
  code(code),
  contentType(contentType),
  contentLength(contentLength) {
}


HttpResponse::HttpResponse(HttpVersion version, HttpResponseCode code, HttpContentType contentType, unsigned contentLength, const std::string& attachmentName)
: version(version),
  code(code),
  contentType(contentType),
  contentLength(contentLength),
  attachmentName(attachmentName) {
}


HttpResponse::~HttpResponse() {
}


std::string HttpResponse::GenerateHeader() const {
    std::stringstream header;
    header << HTTP_VERSION_TO_MESSAGE[version] << " " << code << " " << HTTP_CODE_TO_MESSAGE[code] << "\r\n";
    header << "Content-Type: " << HTTP_CONTENT_TYPE_TO_MESSAGE[contentType] << "\r\n";
    header << "Content-Length: " << contentLength << "\r\n";
    if(!attachmentName.empty())
        header << "Content-Disposition: attachment; filename=" << attachmentName << "\r\n";
    header << "Connection: close\r\n\r\n";
    return header.str();
}
