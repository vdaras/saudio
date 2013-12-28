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

#include "Http.h"


std::map<HttpVersion, const char*> HTTP_VERSION_TO_MESSAGE = {
    { HTTP_1_0, "HTTP/1.0" },
    { HTTP_1_1, "HTTP/1.1" }
};


std::map<HttpResponseCode, const char*> HTTP_CODE_TO_MESSAGE = {
    { OK, "OK" },
    { BAD_REQUEST, "Bad Request" },
    { NOT_FOUND, "Not Found" },
};


std::map<HttpContentType, const char*> HTTP_CONTENT_TYPE_TO_MESSAGE = {
    { MP3,  "audio/mpeg" },
    { MP4,  "audio/mpeg" },
    { M3U,  "audio/mpegurl" },
    { OGG,  "audio/ogg" },
    { WAV,  "audio/wav" },
    { NONE, "" }
};