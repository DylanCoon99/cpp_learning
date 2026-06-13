// Exercise 4: Type Conversions
//
// Task: Explore implicit conversions, static_cast, and narrowing.
//
// Part A — Implicit conversions:
//   - Assign 3.14 to an int variable. Print it. (What happens?)
//   - Assign 42 to a double variable. Print it. (What happens?)
//   - Assign 256 to a char variable. Print the char and its integer value.
//     (Hint: static_cast<int>(ch) to print the numeric value of a char)
//
// Part B — static_cast:
//   - Divide 7 by 2 using integer division. Print the result.
//   - Now divide 7 by 2 using static_cast to get a double result. Print it.
//     Hint: static_cast<double>(7) / 2
//
// Part C — Brace initialization narrowing check:
//   - Try: int x{3.14};
//   - Observe the compiler error. Comment it out after seeing it.
//   - This is why brace initialization is "safer" — it catches accidental
//     data loss.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_conversions.cpp

// YOUR CODE HERE
#include<iostream>


int main() {


	// Part A
	int a = 3.14; // should truncate the decimal
	double b = 42;
	char c = 256;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << " " << static_cast<int>(c) << std::endl;


	// Part B
	std::cout << 7/ 2 << std::endl;
	std::cout << static_cast<double>(7)/ 2 << std::endl;

	// Part C
	//int x{3.14};   // should cause an error
	



}