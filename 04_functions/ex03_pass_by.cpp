// Exercise 3: Pass by Value, Reference, and Const Reference
//
// Task: Write three functions that demonstrate the difference.
//
// Part A: Write these three functions:
//
//   void triple_val(int x)       — multiplies x by 3 (by value)
//   void triple_ref(int& x)     — multiplies x by 3 (by reference)
//   void print_info(const std::vector<int>& v)  — prints size and all elements
//
//   In main(), demonstrate that triple_val does NOT change the original,
//   triple_ref DOES change the original, and print_info reads without copying.
//
// Part B: Write a swap function:
//   void swap(int& a, int& b)
//   Swap two integers using references. (Yes, std::swap exists — write your own.)
//
// Part C: Write a function that returns multiple values through reference params:
//   void min_max(const std::vector<int>& v, int& min_out, int& max_out)
//   Finds the minimum and maximum values in a vector and writes them to
//   the output parameters.
//
//   In main(), create a vector, call min_max, and print the results.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_pass_by.cpp
//
// Note: Returning multiple values via output parameters (Part C) is the old
// C/C++ style. Later we'll learn about std::pair, std::tuple, and structured
// bindings which are the modern way.

// YOUR CODE HERE
