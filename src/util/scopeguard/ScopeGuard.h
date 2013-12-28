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

#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

/**
 * Class with purpose to rollback an operation when its objects
 * get out of scope. If the ScopeGuard is dismissed then it won't
 * rollback the operation.
 */
class ScopeGuard {
  
    mutable bool dismissed;

    protected:

    /**
     * Constructor.
     */
    ScopeGuard();

    public:

    /**
     * Move constructor.
     */
    ScopeGuard(ScopeGuard&& rvalue);
    
    /**
     * Destructor.
     */
    virtual ~ScopeGuard();

    /**
     * Dismisses the scope guard. If a scope guard is 
     * dismissed it won't rollback the operation.
     */
    void Dismiss() const;

    protected:

    /**
     * @return
     *         Whether this scope guard is dismissed or not.
     */
    bool IsDismissed() const;


    ScopeGuard(const ScopeGuard& copy) = delete;

    ScopeGuard& operator=(const ScopeGuard& other) = delete;

    ScopeGuard& operator=(const ScopeGuard&& rvalue) = delete;
};

#endif