/**
 * Copyright (c) 2011-2017s, Vasileios Daras. All rights reserved.
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

    std::unique_ptr<std::thread[]> workingThreads;

    unsigned short totalThreads;

    bool running;

    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;

    std::condition_variable resumeWorker;

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
     * Initialises and starts the workers.
     */
    void Startup();

    /**
     * Shuts the workers down.
     */
    void Shutdown();

    /**
     * Adds a task to the queue.
     */
    template<class Task>
    void EnqueueTask(Task&& task) {

        {
            std::lock_guard<std::mutex> queueLock(queueMutex);
            tasks.push(std::forward<Task>(task));
        }
        resumeWorker.notify_one();
    }

    private:

    /**
     * Pops a task from the queue and runs it. 
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
    void DequeueTask(std::function<void()>* taskOut);
};

#endif