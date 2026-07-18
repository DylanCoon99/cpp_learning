#include "thread_pool.h"
#include <iostream>
#include <chrono>
#include <numeric>
#include <cmath>

int main() {
    ThreadPool pool(4);

    std::cout << "Thread pool with " << pool.num_workers() << " workers\n\n";

    // === Basic task submission ===
    std::cout << "=== Basic Tasks ===\n";
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 8; ++i) {
        futures.push_back(pool.submit([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return i * i;
        }));
    }

    for (int i = 0; i < 8; ++i) {
        std::cout << i << "^2 = " << futures[i].get() << "\n";
    }

    // === Parallel computation ===
    std::cout << "\n=== Parallel Sum ===\n";
    // Split summing 1..1000000 across 4 tasks
    const int N = 1000000;
    const int chunks = 4;
    const int chunk_size = N / chunks;

    std::vector<std::future<long long>> sum_futures;
    for (int c = 0; c < chunks; ++c) {
        int start = c * chunk_size + 1;
        int end = (c + 1) * chunk_size;
        sum_futures.push_back(pool.submit([start, end]() {
            long long sum = 0;
            for (int i = start; i <= end; ++i) sum += i;
            return sum;
        }));
    }

    long long total = 0;
    for (auto& f : sum_futures) total += f.get();
    std::cout << "Sum 1.." << N << " = " << total << "\n";
    std::cout << "Expected: " << (long long)N * (N + 1) / 2 << "\n";

    // === Mixed return types ===
    std::cout << "\n=== Mixed Tasks ===\n";
    auto f1 = pool.submit([]() { return 42; });
    auto f2 = pool.submit([]() { return 3.14; });
    auto f3 = pool.submit([]() { return std::string("hello from pool"); });

    std::cout << "int result: " << f1.get() << "\n";
    std::cout << "double result: " << f2.get() << "\n";
    std::cout << "string result: " << f3.get() << "\n";

    // === Stress test ===
    std::cout << "\n=== Stress Test (100 tasks) ===\n";
    std::atomic<int> completed{0};
    std::vector<std::future<void>> stress_futures;

    for (int i = 0; i < 100; ++i) {
        stress_futures.push_back(pool.submit([&completed]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ++completed;
        }));
    }

    for (auto& f : stress_futures) f.get();
    std::cout << "Completed: " << completed << " / 100\n";

    std::cout << "\nPool shutting down...\n";
}
