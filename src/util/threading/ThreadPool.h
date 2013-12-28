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

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

//standard library includes
#include <atomic>
#include <list>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


/**
 * Class managing a pool of threads.
 */
class ThreadPool {

    std::atomic_bool running;

    std::vector<std::thread> workingThreads;

    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;

    public:

    /**
     * Constructor. 
     *
     * @param totalThreads
     *        Total working threads to create in the pool.
     */
    ThreadPool(unsigned short totalThreads);


    /**
     * Destructor.
     */
    ~ThreadPool();


    /**
     * Adds a task to the queue.
     */
    void EnqueueTask(const std::function<void()>& task);

    private:

    /**
     * Pops a task from the queue and runs it. If there are no
     * available tasks, current thread yields.
     */
    void Worker();


    /**
     * Dequeues a task.
     *
     * @param taskOut
     *        Task returned in here.
     *
     * @return
     *         Whether there was a task to dequeue or not.     
     */
    bool DequeueTask(std::function<void()>* taskOut);
};

#endif