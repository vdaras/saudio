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

#ifndef SIMPLE_SCOPE_GUARD_H
#define SIMPLE_SCOPE_GUARD_H

#include "ScopeGuard.h"

//standard library includes
#include <functional>

typedef std::function<void() noexcept> Callback;

/**
 * A scope guard that calls a function in its destructor if not dismissed.
 */
class SimpleScopeGuard : public ScopeGuard {

    Callback rollbackFunction;

    public:

    /**
     * Constructor.
     *
     * @param rollbackFunction
     *        Function to call if not dismissed.
     */
    SimpleScopeGuard(const Callback& rollbackFunction);

    /**
     * Destructor.
     */
    ~SimpleScopeGuard();
};

#endif