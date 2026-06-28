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
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <unordered_set>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>


int main() {


	std::mt19937 gen(42);  // fixed seed for reproducibility
	std::uniform_int_distribution<int> dist(1, 1000000);

	{
		// Part A — Insertion benchmark:

		// vector
		std::vector<int> v;
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			v.push_back(dist(gen));
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Vector Insertion at Back Time: " << duration.count() << " μs\n";


		// queue
		std::deque<int> q;
		start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			q.push_back(dist(gen));
		}

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Deque Insertion at Back Time: " << duration.count() << " μs\n";

		
		// list
		std::list<int> l;
		start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			l.push_back(dist(gen));
		}

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "List Insertion at Back Time: " << duration.count() << " μs\n";
		std::cout << std::endl;
	}

	
	{
		// Part B — Lookup benchmark:
	
		// vector
		std::vector<int> v;
		for (int i = 0; i < 10000; ++i) {
			v.push_back(dist(gen));
		}
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			std::find(v.begin(), v.end(), dist(gen));
		}

	
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Vector Lookup Time: " << duration.count() << " μs\n";


		// set
		std::set<int> s;
		for (int i = 0; i < 10000; ++i) {
			s.insert(dist(gen));
		}
		start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			s.find(dist(gen));
		}


		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Set Lookup Time: " << duration.count() << " μs\n";

	
	
		// unordered_set
		std::unordered_set<int> unordered_s;
		for (int i = 0; i < 10000; ++i) {
			unordered_s.insert(dist(gen));
		}
		start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			s.find(dist(gen));
		}

	
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Unordered Set Lookup Time: " << duration.count() << " μs\n";
		std::cout << std::endl;

	}

		{
		// Part C — Insertion at front:

		// vector
		std::vector<int> v;
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			v.insert(v.begin(), dist(gen));
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Vector Insertion at Front Time: " << duration.count() << " μs\n";


		// queue
		std::deque<int> q;
		start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			q.push_front(dist(gen));
		}

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Deque Insertion at Front Time: " << duration.count() << " μs\n";

		
		// list
		std::list<int> l;
		start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 10000; ++i) {
			l.push_front(dist(gen));
		}

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "List Insertion at Front Time: " << duration.count() << " μs\n";
		std::cout << std::endl;
	}

	{
		// Part D — Sorted iteration:

		// vector
		std::vector<int> v;
		for (int i = 0; i < 10000; ++i) {
			v.push_back(dist(gen));
		}

		auto start = std::chrono::high_resolution_clock::now();

		// sort here
		std::sort(v.begin(), v.end());


		auto end_sort = std::chrono::high_resolution_clock::now();

		volatile int sink = 0;
		for (int x : v) {
			sink = x;
		}


		auto end_iterate = std::chrono::high_resolution_clock::now();


		auto duration_iterate = std::chrono::duration_cast<std::chrono::microseconds>(end_iterate - start);
		auto duration_sort = std::chrono::duration_cast<std::chrono::microseconds>(end_sort - start);
		std::cout << "Vector Sort Time: " << duration_sort.count() << " μs\n";
		std::cout << "Vector Sort + Iteration Time: " << duration_iterate.count() << " μs\n";


		// set
		std::set<int> s;
		for (int i = 0; i < 10000; ++i) {
			s.insert(dist(gen));
		}

		start = std::chrono::high_resolution_clock::now();

		for (int x : s) {
			sink = x;
		}


		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << "Set Iteration Time: " << duration.count() << " μs\n";


	}




}
