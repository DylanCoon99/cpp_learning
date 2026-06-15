// Exercise 2: auto Type Deduction
//
// Task: Declare variables using auto and verify their types.
//
// Requirements:
//   - Declare auto variables initialized with:
//       42, 3.14, 3.14f, true, 'A', "hello"
//   - For each, print the value
//   - Use typeid(var).name() to print the compiler's internal type name
//       (requires #include <typeinfo>)
//   - Note: typeid names are compiler-specific and mangled (e.g., "i" for int
//     on GCC). That's fine — the goal is to see that different literals
//     produce different types.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_auto.cpp
// Example output (GCC):
//   42 has type: i
//   3.14 has type: d
//   3.14f has type: f
//   true has type: b
//   'A' has type: c
//   "hello" has type: PKc
//
// Question to consider: "hello" is NOT a std::string by default. What is it?
// (Hint: PKc = pointer to const char. It's a C-string literal, same as in C.)

// YOUR CODE HERE
#include <iostream>


int main() {


	auto value1 = 42;      // should be an int
	auto value2 = 3.14;    // should be a double
	auto value3 = 3.14f;   // should be a float
	auto value4 = true;    // should be a bool
	auto value5 = 'A';     // should be a char
	auto value6 = "hello"; // std::string ?? -> No it is char*, a P(ointer)K(onstant)c(har)

	std::cout << value1 << " has type: " << typeid(value1).name() << std::endl;
	std::cout << value2 << " has type: " << typeid(value2).name() << std::endl;
	std::cout << value3 << " has type: " << typeid(value3).name() << std::endl;
	std::cout << value4 << " has type: " << typeid(value4).name() << std::endl;
	std::cout << value5 << " has type: " << typeid(value5).name() << std::endl;
	std::cout << value6 << " has type: " << typeid(value6).name() << std::endl;


}