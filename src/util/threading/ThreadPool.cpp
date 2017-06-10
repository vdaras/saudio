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

#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned short totalThreads)
: totalThreads(totalThreads)
, running(false) {
}


ThreadPool::~ThreadPool() {
    if(running) {
        Shutdown();
    }
}

void ThreadPool::Startup() {

    if(!running) {
        running = true;
        decltype(workingThreads) tempWorkingThreads(new std::thread[totalThreads]);
        for(unsigned short i = 0; i < totalThreads; i++) {
            tempWorkingThreads[i] = std::thread(&ThreadPool::Worker, this);
        }
        workingThreads.swap(tempWorkingThreads);
    }
}

void ThreadPool::Shutdown() {

    if(running) {
        running = false;
        resumeWorker.notify_all();
        for(unsigned short i = 0; i < totalThreads; i++) {
            if(workingThreads[i].joinable()) {
                workingThreads[i].join();
            }
        }
        workingThreads.reset();
    }
}

void ThreadPool::Worker() {
    
    while(true) {

        std::unique_lock<std::mutex> lock(queueMutex);
        resumeWorker.wait(lock, [this] {
            return !running || !tasks.empty();
        });

        if(!running)
            return;

        std::function<void()> task;
        DequeueTask(&task);
        lock.unlock();
        
        task();
    }
}


void ThreadPool::DequeueTask(std::function<void()>* taskOut) {
    *taskOut = tasks.front();
    tasks.pop();
}

