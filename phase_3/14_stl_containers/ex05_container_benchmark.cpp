// Exercise 5: Container Performance Comparison
//
// Task: Measure and compare the performance of different containers
//       for various operations. This builds intuition for choosing
//       the right container.
//
// Use <chrono> for timing:
//   #include <chrono>
//   auto start = std::chrono::high_resolution_clock::now();
//   // ... operation ...
//   auto end = std::chrono::high_resolution_clock::now();
//   auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//   std::cout << "Time: " << duration.count() << " μs\n";
//
// Part A — Insertion benchmark:
//   Insert N = 100000 random integers into each:
//     - std::vector (push_back)
//     - std::deque (push_back)
//     - std::list (push_back)
//     - std::set
//     - std::unordered_set
//   Print the time for each.
//
// Part B — Lookup benchmark:
//   Search for 10000 random values in each container:
//     - std::vector (linear search with std::find)
//     - std::set (s.find())
//     - std::unordered_set (s.find())
//   Print the time for each. Observe the dramatic difference.
//
// Part C — Insertion at front:
//   Insert 100000 elements at the front:
//     - std::vector (insert at begin)
//     - std::deque (push_front)
//     - std::list (push_front)
//   Print times. Vector should be dramatically slower.
//
// Part D — Sorted iteration:
//   Store 100000 elements, then iterate through all in sorted order:
//     - std::vector (sort first, then iterate)
//     - std::set (already sorted, just iterate)
//   Compare total time (sort + iterate vs just iterate).
//
// Part E — Summary table:
//   Print a formatted table of all results:
//
//   | Operation        | vector   | deque    | list     | set      | unord_set |
//   |------------------|----------|----------|----------|----------|-----------|
//   | push_back 100k   | 1234 μs  | ...      | ...      | ...      | ...       |
//   | find 10k         | ...      | N/A      | N/A      | ...      | ...       |
//   | push_front 100k  | ...      | ...      | ...      | N/A      | N/A       |
//
// Use std::setw for alignment.
//
// Generate random numbers:
//   #include <random>
//   std::mt19937 gen(42);  // fixed seed for reproducibility
//   std::uniform_int_distribution<int> dist(1, 1000000);
//   int value = dist(gen);
//
// Compile: g++ -std=c++20 -Wall -Wextra -O2 -o ex05 ex05_container_benchmark.cpp
// Note: -O2 enables optimization — important for meaningful benchmarks

// YOUR CODE HERE
