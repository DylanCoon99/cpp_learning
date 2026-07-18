#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>
#include <vector>
#include <functional>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(int num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

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

    int pending() const;
    int num_workers() const;

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<bool> stop_{false};

    void worker_loop();
};
