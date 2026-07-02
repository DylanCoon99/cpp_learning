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


class Range {

public:
	using iterator_category = std::forward_iterator_tag;   // "I can go forward"
	using value_type = int;                                // "I produce ints"                                                                                                     
	using difference_type = std::ptrdiff_t;                // "distance between iterators"
	using pointer = const int*;                            // "pointer to my values"                                                                                               
	using reference = const int&;                          // "reference to my values"

	Range(int start, int end, int step = 1) : start_(start), end_(end), step_(step) { }


	Range operator*(const Range& range) {

	}

	Range operator++(const int inc) {
		
	}

	bool operator==(const Range& range) {
		
	}

	bool operator!=(const Range& range) {
		
	}



private:
	int start_, end_, step_;

};



int main() {



}
