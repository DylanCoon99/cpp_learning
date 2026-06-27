// Exercise 5: Generic Algorithms
//
// Task: Write generic algorithm functions that work on any container
//       (via iterators or on vectors directly). This previews the STL
//       algorithms we'll cover in step 15.
//
// Part A — Working with vectors of any type:
//
//   template <typename T>
//   int find_index(const std::vector<T>& v, const T& target);
//     — Return index of first occurrence, or -1 if not found
//
//   template <typename T>
//   int count(const std::vector<T>& v, const T& target);
//     — Count how many times target appears
//
//   template <typename T>
//   T accumulate(const std::vector<T>& v, T initial);
//     — Sum all elements starting from initial value
//     — Works for int (sum), string (concatenation), etc.
//
//   template <typename T>
//   std::vector<T> filter(const std::vector<T>& v, bool (*predicate)(const T&));
//     — Return a new vector with only elements where predicate returns true
//
//   Test each with at least two different types.
//
// Part B — Transform:
//
//   template <typename T, typename U>
//   std::vector<U> transform(const std::vector<T>& v, U (*func)(const T&));
//     — Apply func to each element, return vector of results
//     — T and U can be different types!
//
//   Test:
//     vector<int> → vector<int> (square each)
//     vector<string> → vector<int> (get length of each)
//     vector<int> → vector<string> (convert to string)
//
// Part C — Generic sort with comparator:
//
//   template <typename T>
//   void my_sort(std::vector<T>& v, bool (*compare)(const T&, const T&));
//     — Sort using the provided comparison function
//     — Implement bubble sort or selection sort (simplicity over efficiency)
//
//   Write comparator functions:
//     bool ascending(const int& a, const int& b) { return a < b; }
//     bool descending(const int& a, const int& b) { return a > b; }
//     bool by_length(const std::string& a, const std::string& b) {
//         return a.size() < b.size();
//     }
//
//   Test: sort ints ascending, descending. Sort strings by length.
//
// Part D — Chaining:
//   Demonstrate using your functions together:
//     - Create a vector<int> of numbers
//     - filter for even numbers
//     - transform to double each
//     - accumulate to sum them
//     - Print the result
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_algorithms.cpp

// YOUR CODE HERE
#include <vector>
#include <iostream>
#include <string>


// Part A
template <typename T>
int find_index(const std::vector<T>& v, const T& target) {
	//     — Return index of first occurrence, or -1 if not found
	int idx = -1;

	for (int i = 0; i < static_cast<int>(v.size()); ++i) {
		if (v[i] == target) {
			idx = i;
			break;
		}
	}

	return idx;
}


template <typename T>
int count(const std::vector<T>& v, const T& target) {
	//     — Count how many times target appears

	int count = 0;

	for (auto &elem : v) {
		if (elem == target) {
			++count;
		}
	}
	return count;
}


template <typename T>
T accumulate(const std::vector<T>& v, T initial) {
	//     — Sum all elements starting from initial value
	//     — Works for int (sum), string (concatenation), etc.
	T result = initial;

	for (auto & elem : v) {
		result += elem;
	}

	return result;
}


template <typename T>
std::vector<T> filter(const std::vector<T>& v, bool (*predicate)(const T&)) {
	std::vector<T> result;

	for (auto &e : v) {
		if (predicate(e)) {
			result.push_back(e);
		}
	}

	return result;

}

bool is_even(const int& a) {
	return a % 2 == 0;
}

// Part B
template <typename T, typename U>
std::vector<U> transform(const std::vector<T>& v, U (*func)(const T&)) {
	//     — Apply func to each element, return vector of results
	//     — T and U can be different types!
	std::vector<U> result;

	for (auto & elem : v) {
		result.push_back(std::move(func(elem)));
	}
	return result;
}


int square(const int& a) {
	return a * a;
}


std::string to_string(const int& a) {
	return std::to_string(a);
}

int length(const std::string& str) {
	return str.length();
}

int times_two(const int& a) {
	return a * 2;
}


// Part C
template <typename T>
void my_sort(std::vector<T>& v, bool (*compare)(const T&, const T&)) {
	//     — Sort using the provided comparison function
	//     — Implement bubble sort or selection sort (simplicity over efficiency)
	for (int i = 0; i < static_cast<int>(v.size()); ++i) {
		// iterate over rest of vector
		T min = v[i];
		int idx = i;
		for (int j = i; j < static_cast<int>(v.size()); ++j) {
			// find min in the rest of the list
			if (compare(v[j], min)) {
				min = v[j];
				idx = j;
			}
		}
		// swap
		T temp = v[i];
		v[i] = v[idx];
		v[idx] = temp;
	}
}



bool ascending(const int& a, const int& b) { return a < b; }


bool descending(const int& a, const int& b) { return a > b; }


bool by_length(const std::string& a, const std::string& b) {
	return a.size() < b.size();
}



int main() {

	{
		// Part A — find_index
		std::vector<int> nums = {10, 20, 30, 40, 50};
		std::cout << "find_index 30: " << find_index(nums, 30) << std::endl;      // 2
		std::cout << "find_index 99: " << find_index(nums, 99) << std::endl;      // -1

		std::vector<std::string> words = {"hello", "world", "foo", "bar"};
		std::cout << "find_index foo: " << find_index(words, std::string("foo")) << std::endl;  // 2
		std::cout << "find_index baz: " << find_index(words, std::string("baz")) << std::endl;  // -1

		// Part A — count
		std::vector<int> nums2 = {1, 2, 3, 2, 4, 2, 5};
		std::cout << "count 2: " << count(nums2, 2) << std::endl;      // 3
		std::cout << "count 9: " << count(nums2, 9) << std::endl;      // 0

		std::vector<char> chars = {'a', 'b', 'a', 'c', 'a'};
		std::cout << "count 'a': " << count(chars, 'a') << std::endl;  // 3

		// Part A — accumulate
		std::cout << "sum ints: " << accumulate(nums, 0) << std::endl;             // 150
		std::cout << "sum doubles: " << accumulate(std::vector<double>{1.5, 2.5, 3.0}, 0.0) << std::endl;  // 7.0

		std::vector<std::string> strs = {"hello", " ", "world"};
		std::cout << "concat strings: " << accumulate(strs, std::string("")) << std::endl;  // "hello world"

	// Part B — transform
		// vector<int> → vector<int> (square each)
		std::vector<int> squared = transform(nums, square);
		std::cout << "squared: ";
		for (auto& n : squared) std::cout << n << " ";
		std::cout << std::endl;  // 100 400 900 1600 2500

		// vector<string> → vector<int> (get length of each)
		std::vector<int> lengths = transform(words, length);
		std::cout << "lengths: ";
		for (auto& n : lengths) std::cout << n << " ";
		std::cout << std::endl;  // 5 5 3 3

		// vector<int> → vector<string> (convert to string)
		std::vector<std::string> as_strings = transform(nums, to_string);
		std::cout << "as strings: ";
		for (auto& s : as_strings) std::cout << "\"" << s << "\" ";
		std::cout << std::endl;  // "10" "20" "30" "40" "50"
	}


	{
		// Part C
		std::vector<int> v = {6, 7, 3, 4, 2, 0, 9};
		my_sort(v, ascending);
		for (auto &e : v) {
			std::cout << e << " ";
		}
		std::cout << std::endl;


		my_sort(v, descending);
		for (auto &e : v) {
			std::cout << e << " ";
		}
		std::cout << std::endl;

		std::vector<std::string> strs = {"hello", "this", "is", "my", "string", "testing"};
		my_sort(strs, by_length);
		for (auto &e : strs) {
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	{
		//   Demonstrate using your functions together:
		//     - Create a vector<int> of numbers
		//     - filter for even numbers
		//     - transform to double each
		std::cout << "sum: " << accumulate(transform(filter({3, 4, 7, 2, 3, 1}, is_even), times_two), 0) << std::endl;
		//     - accumulate to sum them
		//     - Print the result
	}


}

