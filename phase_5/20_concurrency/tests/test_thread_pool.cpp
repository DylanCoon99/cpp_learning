#include <gtest/gtest.h>
#include "thread_pool.h"
#include <numeric>

TEST(ThreadPoolTest, SubmitAndGetResult) {
    ThreadPool pool(2);
    auto f = pool.submit([]() { return 42; });
    EXPECT_EQ(f.get(), 42);
}

TEST(ThreadPoolTest, MultipleTasksComplete) {
    ThreadPool pool(4);
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 20; ++i) {
        futures.push_back(pool.submit([i]() { return i * 2; }));
    }

    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(futures[i].get(), i * 2);
    }
}

TEST(ThreadPoolTest, TasksRunConcurrently) {
    ThreadPool pool(4);
    std::atomic<int> running{0};
    std::atomic<int> max_running{0};
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 4; ++i) {
        futures.push_back(pool.submit([&running, &max_running]() {
            int current = ++running;
            // Track max concurrent tasks
            int prev_max = max_running.load();
            while (current > prev_max && !max_running.compare_exchange_weak(prev_max, current));

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            --running;
        }));
    }

    for (auto& f : futures) f.get();
    EXPECT_GT(max_running.load(), 1);  // at least 2 ran concurrently
}

TEST(ThreadPoolTest, DifferentReturnTypes) {
    ThreadPool pool(2);

    auto f_int = pool.submit([]() { return 10; });
    auto f_double = pool.submit([]() { return 3.14; });
    auto f_string = pool.submit([]() { return std::string("test"); });

    EXPECT_EQ(f_int.get(), 10);
    EXPECT_DOUBLE_EQ(f_double.get(), 3.14);
    EXPECT_EQ(f_string.get(), "test");
}

TEST(ThreadPoolTest, NumWorkersMatchesRequested) {
    ThreadPool pool(6);
    EXPECT_EQ(pool.num_workers(), 6);
}

TEST(ThreadPoolTest, StressTest) {
    ThreadPool pool(4);
    std::atomic<int> counter{0};
    std::vector<std::future<void>> futures;

    for (int i = 0; i < 200; ++i) {
        futures.push_back(pool.submit([&counter]() {
            ++counter;
        }));
    }

    for (auto& f : futures) f.get();
    EXPECT_EQ(counter.load(), 200);
}

TEST(ThreadPoolTest, ParallelSum) {
    ThreadPool pool(4);
    const int N = 10000;
    const int chunks = 4;
    const int chunk_size = N / chunks;

    std::vector<std::future<long long>> futures;
    for (int c = 0; c < chunks; ++c) {
        int start = c * chunk_size + 1;
        int end = (c + 1) * chunk_size;
        futures.push_back(pool.submit([start, end]() {
            long long sum = 0;
            for (int i = start; i <= end; ++i) sum += i;
            return sum;
        }));
    }

    long long total = 0;
    for (auto& f : futures) total += f.get();
    EXPECT_EQ(total, (long long)N * (N + 1) / 2);
}
