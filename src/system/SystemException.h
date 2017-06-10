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

#ifndef SYSTEM_EXCEPTION_H
#define SYSTEM_EXCEPTION_H

#include "util/exception/BaseException.h"

//standard library includes
#include <exception>
#include <string>

class SystemException : public BaseException {

    public:

    SystemException(const std::string& message);

    virtual ~SystemException() noexcept;

};

class UnsupportedOSException : SystemException {

    public:

    UnsupportedOSException();

    virtual ~UnsupportedOSException() noexcept;    
};

#endif