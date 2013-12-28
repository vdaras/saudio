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

#include "PercentUrlCodec.h"

bool PercentURLCodec::IsReservedCharacter(char c)
{
    return c == '/'  ||
           c == ','  ||
           c == '\'' ||
           c == ':'  ||
           c == ';'  ||
           c == '&'  ||
           c == '='  ||
           c == '@'  ||
           c == '('  ||
           c == ')'  ||
           c == '['  ||
           c == ']'  ||
           c == '?'  ||
           c == '$'  ||
           c == '#'  ||
           c == '+'  ||
           c == '*'  ||
           c == '!'  ;
}

char PercentURLCodec::FromHex(char ch)
{
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

std::string PercentURLCodec::EncodeURL(const std::string& url) const
{
    static const char hex[] = "0123456789abcdef";

    int urlLength = url.length();

    //allocate a string big enough for the worst-case scenario (all chars in the url need to be encoded)
    std::string encodedUrl;
    encodedUrl.reserve(urlLength * 3);

for(const char& c : url)
    {
        if(IsReservedCharacter(c))
        {
            encodedUrl += '%';
            encodedUrl += hex[(c >> 4) & 15];
            encodedUrl += hex[(c & 15) & 15];
        }
        else if(c == ' ')
        {
            encodedUrl += '+';
        }
        else
        {
            encodedUrl += c;
        }
    }

    return encodedUrl;
}


std::string PercentURLCodec::DecodeURL(const std::string& encodedUrl) const
{
    int urlLength = encodedUrl.length();

    //allocate a string big enough for the worst-case scenario (all chars in the url are not encoded)
    std::string decodedUrl;
    decodedUrl.reserve(urlLength);

    for(int i = 0; i < urlLength;)
    {

        char c = encodedUrl[i];

        if(c == '%')
        {

            if(i + 2 < urlLength)
            {
                decodedUrl += FromHex(encodedUrl[i+1]) << 4 | FromHex(encodedUrl[i+2]);
            }

            i += 3;

        }
        else if(c == '+')
        {
            decodedUrl += ' ';
            i++;
        }
        else
        {
            decodedUrl += c;
            i++;
        }
    }

    return decodedUrl;
}