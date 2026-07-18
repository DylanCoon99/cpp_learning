#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>
#include <vector>
#include <functional>
#include <future>
#include <iostream>

// A thread pool that manages a fixed number of worker threads.
// Tasks are submitted and executed by the next available worker.
//
// This is a real-world pattern used in web servers, game engines,
// and parallel computing.

class ThreadPool {
public:
    // Create pool with 'num_threads' workers (default: hardware concurrency)
    explicit ThreadPool(int num_threads = std::thread::hardware_concurrency());

    // No copying or moving
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // Submit a task — returns a future to get the result
    // This is the key method. It should:
    //   1. Wrap the task in a std::packaged_task
    //   2. Get the future from the packaged_task
    //   3. Push the task onto the queue (lock the mutex)
    //   4. Notify one waiting worker
    //   5. Return the future
    template <typename F>
    std::future<typename std::invoke_result_t<F>> submit(F task) {
        using ReturnType = typename std::invoke_result_t<F>;

        auto packaged = std::make_shared<std::packaged_task<ReturnType()>>(std::move(task));
        std::future<ReturnType> result = packaged->get_future();

        {
            std::lock_guard<std::mutex> lock(mtx_);
            tasks_.push([packaged]() { (*packaged)(); });
        }
        cv_.notify_one();

        return result;
    }

    // Get number of pending tasks
    int pending() const;

    // Get number of worker threads
    int num_workers() const;

    // Shutdown — stop accepting tasks, finish all pending, join all threads
    ~ThreadPool();

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> stop_{false};

    // Worker loop — each thread runs this
    void worker_loop();
};
