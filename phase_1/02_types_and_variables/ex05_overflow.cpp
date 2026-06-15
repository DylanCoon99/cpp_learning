// Exercise 5: Integer Overflow
//
// Task: Explore what happens when integers overflow in C++.
//
// Requirements:
//   - #include <climits> (or <limits>) to access INT_MAX, INT_MIN, etc.
//   - Print INT_MAX and INT_MIN
//   - Add 1 to INT_MAX and print the result. What happens?
//   - Subtract 1 from INT_MIN and print the result. What happens?
//   - Do the same with unsigned: print UINT_MAX, then UINT_MAX + 1
//   - Print the max value of a uint8_t (hint: cast to int before printing,
//     otherwise cout treats uint8_t as a char)
//
// Key takeaway: signed integer overflow is UNDEFINED BEHAVIOR in C++ (same
// as C). The compiler is allowed to assume it never happens and can optimize
// based on that assumption. Unsigned overflow wraps around (defined behavior).
//
// This is different from Go, where signed integer overflow is defined to wrap.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_overflow.cpp

// YOUR CODE HERE
#include<climits>
#include<iostream>


int main() {

	std::cout << "INT_MAX: " << INT_MAX << std::endl;
	std::cout << "INT_MIN: " << INT_MIN << std::endl;

	std::cout << "INT_MAX: " << INT_MAX + 1 << std::endl;
	std::cout << "INT_MIN: " << INT_MIN - 1<< std::endl;

	// When we add to the INT_MAX or subtract from INT_MIN -> integer overflow

	std::cout << "INT_MAX: " << UINT_MAX << std::endl;

	std::cout << "INT_MAX: " << UINT_MAX + 1 << std::endl;

	// UINT_MAX rolls back to 0 because it's range is 0 —— 4294967295

	



}