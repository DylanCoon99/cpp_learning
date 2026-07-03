// Exercise 5: Custom Iterator — Python-like Range
//
// Task: Build a Range class that generates numbers lazily and works
//       with range-based for loops and STL algorithms. This is the
//       only exercise where you build an iterator from scratch.
//
// Class: Range
//   Range(int start, int end, int step = 1)
//
//   Must support:
//     - Range-based for:  for (int x : Range(0, 10)) { ... }
//     - STL algorithms:   std::accumulate(r.begin(), r.end(), 0)
//     - Negative steps:   Range(10, 0, -1) counts down
//     - Construction into vector: std::vector<int> v(r.begin(), r.end())
//
// You need a nested Iterator class with:
//   - Type aliases (iterator_category, value_type, difference_type, pointer, reference)
//   - operator*, operator++, operator== , operator!=
//
// See the README for the full class skeleton.
//
// Test by using Range in the following ways:
//   - for (int x : Range(0, 10))          → 0 1 2 3 4 5 6 7 8 9
//   - for (int x : Range(0, 20, 3))       → 0 3 6 9 12 15 18
//   - for (int x : Range(10, 0, -1))      → 10 9 8 7 6 5 4 3 2 1
//   - std::accumulate on Range(1, 101)    → 5050
//   - std::count_if for evens in Range(1, 21)  → 10
//   - std::find in Range(0, 100) for value 42
//   - Construct vector from Range
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_custom_iterator.cpp

// YOUR CODE HERE
#include <iterator>
#include <iostream>
#include <numeric>
#include <vector>


class Range {

public:

	Range(int start, int end, int step = 1) : start_(start), end_(end), step_(step) {}

	class Iterator {
    public:
        // Required type aliases — STL algorithms query these
        using iterator_category = std::forward_iterator_tag;  // what kind of iterator
        using value_type = int;              // what type it produces
        using difference_type = std::ptrdiff_t;  // type for distances
        using pointer = const int*;          // pointer to value
        using reference = const int&;        // reference to value

        // Constructor
        Iterator(int value, int step) : current_(value), step_(step) {}

        // Dereference — return the current value
        int operator*() const { return current_; }

        // Pre-increment — advance to next element, return *this
        Iterator& operator++() {
            current_+=step_;
            return *this;
        }

        // Post-increment — save old state, advance, return old
        Iterator operator++(int) {
            Iterator old = *this;
            current_+=step_;
            return old;
        }

        // Equality — needed for the != end() check in for loops
        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) const {
			if (step_ > 0) return current_ < other.current_;                                                                                                                             
			if (step_ < 0) return current_ > other.current_;                                                                                                                               
			return false; 
        }

    private:
        int current_;
        int step_;
    };


    Iterator begin() const { return Iterator(start_, step_); }
    Iterator end() const { return Iterator(end_, step_); }



private:
	int start_, end_, step_;

};



int main() {


	for (int x : Range(0, 10)) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;
	for (int x : Range(0, 20, 3)) {
		std::cout << x << std::endl;
	}
	std::cout << std::endl;
	
	for (int x : Range(10, 0, -1)) {
		std::cout << x << std::endl;
	}

	Range r(1, 101);
	std::cout << "Sum 1-101: " << std::accumulate(r.begin(), r.end(), 0) << std::endl;
	
	std::cout << "count_if for evens: " << std::count_if(r.begin(), r.end(), [](const int x) {return x % 2 == 0;}) << std::endl;


	std::cout << "Find(42): " << *std::find(r.begin(), r.end(), 42) << std::endl;

	std::vector<int> v(r.begin(), r.end());

	for (int x : v) {
		std::cout << x << std::endl;
	}
}
