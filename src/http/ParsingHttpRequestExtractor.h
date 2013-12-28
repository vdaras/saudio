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

#ifndef PARSING_HTTP_REQUEST_EXTRACTOR
#define PARSING_HTTP_REQUEST_EXTRACTOR

#include "IHttpRequestExtractor.h"

/**
 * Extracts parts of an HttpRequest by performing parsing on it.
 */
class ParsingHttpRequestExtractor : public IHttpRequestExtractor {

    public:

    std::string ExtractGET(const HttpRequest& request) const override;

    std::string ExtractHOST(const HttpRequest& request) const override;
};

#endif