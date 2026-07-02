// Exercise 1: Iterator Fundamentals
//
// Task: Practice different ways to traverse and manipulate containers
//       using iterators.
//
// Part A — Basic traversal:
//   Create a vector<int> with values 10-100 (step 10).
//   Traverse and print using:
//     1. Index-based for loop
//     2. Iterator-based for loop (auto it = v.begin(); it != v.end(); ++it)
//     3. Range-based for loop
//     4. Reverse iterators (rbegin/rend)
//     5. const iterators (cbegin/cend)
//
// Part B — Iterator arithmetic:
//   - Use std::advance to move an iterator to the 5th element
//   - Use std::next and std::prev to get neighboring elements
//   - Use std::distance to compute how far apart two iterators are
//   - Use iterator subtraction (it2 - it1) for the same thing (vector only)
//
// Part C — Iterating different containers:
//   Create and iterate each, printing all elements:
//     - std::list<std::string> (bidirectional iterators)
//     - std::set<int> (bidirectional iterators)
//     - std::map<std::string, int> (bidirectional, structured bindings)
//   Try: can you use it + 3 on a list iterator? Why not?
//   (list iterators are bidirectional, not random access)
//
// Part D — Modifying through iterators:
//   - Create a vector<int> of 10 elements
//   - Use an iterator loop to double every element
//   - Use an iterator to insert an element in the middle
//     (v.insert(it, value) — returns iterator to inserted element)
//   - Use an iterator to erase every other element
//     (careful: erase invalidates iterators! Use: it = v.erase(it))
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_iterator_basics.cpp

// YOUR CODE HERE
#include <vector>
#include <iostream>
#include <set>
#include <list>
#include <map>




int main() {

	{
		// Part A — Basic traversal:
		std::vector<int> v;
		for (int i = 10; i <= 100; ++i) {
			v.push_back(i);
		}

		//     1. Index-based for loop
		std::cout << "Index-based" << std::endl;
		for (int i = 0; i < static_cast<int>(v.size()); ++i) {
			std::cout << v[i] << std::endl;
		}

		//     2. Iterator-based for loop (auto it = v.begin(); it != v.end(); ++it)
		std::cout << std::endl;
		std::cout << "Iterator-based" << std::endl;
		for (auto it = v.begin(); it != v.end(); ++it) {
			std::cout << *it << std::endl;
		}
		//     3. Range-based for loop
		std::cout << std::endl;
		std::cout << "Range-based" << std::endl;
		for (auto &e : v) {
			std::cout << e << std::endl;
		}

		//     4. Reverse iterators (rbegin/rend)
		std::cout << std::endl;
		std::cout << "Reverse iterators" << std::endl;
		for (auto it = v.rend(); it != v.rbegin() - 1; --it) {
			std::cout << *it << std::endl;
		}
		//     5. const iterators (cbegin/cend)
		std::cout << std::endl;
		std::cout << "const iterators" << std::endl;
		for (auto it = v.cbegin(); it != v.cend(); ++it) {
			std::cout << *it << std::endl;
		}

	}

	{
		// Part B — Iterator arithmetic:
		std::vector<int> v;
		for (int i = 0; i < 100; ++i) {
			v.push_back(i);
		}
		auto it = v.begin();
		std::advance(it, 4);
		std::cout << "5th element: " << *it << std::endl;
		std::cout << "4th element: " << *std::prev(it) << std::endl;
		std::cout << "6th element: " << *std::next(it) << std::endl;
		std::cout << "end - start: " << std::distance(v.begin(), v.end()) << std::endl;
		std::cout << "end - start: " << v.end() - v.begin() << std::endl;


	}

	{
		// Part C — Iterating different containers:

		std::list<std::string> names = {"Alice", "Bob", "Carol", "Dan", "Eve"};
		std::cout << "list: ";
		for (auto it = names.begin(); it != names.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::set<int> nums = {42, 7, 15, 23, 8, 31, 42, 7};
		std::cout << "set: ";
		for (auto it = nums.begin(); it != nums.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::map<std::string, int> ages = {
			{"Alice", 30}, {"Bob", 25}, {"Carol", 28}, {"Dan", 35}, {"Eve", 22}
		};
		std::cout << "map: ";
		for (const auto& [name, age] : ages) {
			std::cout << name << "=" << age << " ";
		}
		std::cout << std::endl;

		// Try: auto it = names.begin(); it + 3;  // ERROR: list is bidirectional, not random access
	}

	{
		// Part D — Modifying through iterators:
		std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

		/*
		for (auto it = v.begin(); it != v.end(); ++it) {
			*it*=2;
		}

		for (auto it = v.begin(); it != v.end(); ++it) {
			std::cout << *it << std::endl;
		}

		for (auto it = v.begin(); it != v.end(); ++it) {
			if (std::distance(v.begin(), it) == v.size() / 2) {
				v.insert(it, 99);
				break;
			}
		}

		for (auto it = v.begin(); it != v.end(); ++it) {
			std::cout << *it << std::endl;
		}
		*/

		auto it = v.begin();
		while (it < v.end()) {
			it = v.erase(it);
			it = std::next(it);
		}

		for (auto it = v.begin(); it != v.end(); ++it) {
			std::cout << *it << std::endl;
		}



	}


}