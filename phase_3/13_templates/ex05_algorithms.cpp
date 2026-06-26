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
