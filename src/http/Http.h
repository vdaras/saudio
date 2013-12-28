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

#ifndef HTTP_PROTOCOL_H
#define HTTP_PROTOCOL_H

//standard library includes
#include <map>
#include <string>

enum HttpVersion {
	HTTP_1_0,
	HTTP_1_1
};

enum HttpResponseCode {
	OK = 200,
	BAD_REQUEST = 400,
	NOT_FOUND = 404
};


enum HttpContentType {
	MP3,
	MP4,
	M3U,
	OGG,
	WAV,
	NONE
};


extern std::map<HttpVersion, const char*> HTTP_VERSION_TO_MESSAGE;

extern std::map<HttpResponseCode, const char*> HTTP_CODE_TO_MESSAGE;

extern std::map<HttpContentType,  const char*> HTTP_CONTENT_TYPE_TO_MESSAGE;

#endif