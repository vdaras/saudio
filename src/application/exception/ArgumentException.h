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

#ifndef ARGUMENT_EXCEPTION_H
#define ARGUMENT_EXCEPTION_H

#include "AudioStreamerException.h"

//standard library includes
#include <string>

class ArgumentException : public AudioStreamerException {
};


class InsufficientArgumentsException : public ArgumentException {
    
    public:

    const char* what() const noexcept override;
};


class InvalidArgumentException : public ArgumentException {
    
    std::string argName;

    std::string argValue;

    public:

    InvalidArgumentException(const std::string& argName, const std::string& argValue);

    const char* what() const noexcept override;
};
#endif