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

#include "SignalHandler.h"

//standard library includes
#include <list>
#include <map>
#include <iostream>

static std::map<int, std::list<SignalHandler>> handlerLists;

void AddSignalHandler(int signal,const SignalHandler& handler)
{
    handlerLists[signal].push_back(handler);
}

void InvokeSignalHandlers(int signal)
{

    if(handlerLists.find(signal) != handlerLists.end())
    {
        std::list<SignalHandler>& handlers = handlerLists[signal];

for(SignalHandler& signalHandler : handlers)
        {
            signalHandler(signal);
        }
    }
};