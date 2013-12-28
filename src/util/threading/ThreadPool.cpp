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

#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned short totalThreads)
    : running(true)
{

    workingThreads.reserve(totalThreads);
    for(unsigned short i = 0; i < totalThreads; i++)
    {
        workingThreads.push_back(std::thread(&ThreadPool::Worker, this));
    }

}


ThreadPool::~ThreadPool()
{

    running = false;

for(std::thread& thread : workingThreads)
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
}


void ThreadPool::EnqueueTask(const std::function<void()>& task)
{
    std::lock_guard<std::mutex> queueLock(queueMutex);
    tasks.push(std::move(task));
}


void ThreadPool::Worker()
{

    while(running)
    {

        std::function<void()> task;
        if(DequeueTask(&task))
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }

    }
}


bool ThreadPool::DequeueTask(std::function<void()>* taskOut)
{
    std::lock_guard<std::mutex> queueLock(queueMutex);
    if(!tasks.empty())
    {
        *taskOut = tasks.front();
        tasks.pop();
        return true;
    }

    return false;
}

