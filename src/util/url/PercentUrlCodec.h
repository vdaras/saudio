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

#ifndef PERCENT_URL_CODEC_H
#define PERCENT_URL_CODEC_H

#include "IUrlCodec.h"

/**
 * Performs percent encoding and decoding on a URL.
 */
class PercentURLCodec : public IURLCodec {
    
    public:

    /**
     * Encodes a URL.
     *
     * @param
     *        URL to encode.
     *
     * @return
     *         The encoded URL.
     */
	std::string EncodeURL(const std::string& url) const override;

    /**
     * Decodes a URL.
     *
     * @param
     *        URL to decode.
     *
     * @return
     *         The decoded URL.
     */
	std::string DecodeURL(const std::string& encodedUrl) const override;


    private:

    /**
     * @return
     *         Whether the input character is reserved or not.
     */
	static bool IsReservedCharacter(char c);

    /**
     * Converts a hex character to the equivalent integer.
     */
	static char FromHex(char ch);
};

#endif