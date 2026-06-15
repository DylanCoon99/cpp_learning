// Exercise 1: Type Sizes
//
// Task: Print the size (in bytes) of each of the following types:
//   char, bool, short, int, long, long long, float, double,
//   int8_t, int16_t, int32_t, int64_t, size_t
//
// Requirements:
//   - #include <cstdint> for the fixed-width types
//   - Use sizeof() for each
//   - Format output like: "int: 4 bytes"
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_sizes.cpp
// Example output (may vary by platform):
//   char:      1 bytes
//   bool:      1 bytes
//   short:     2 bytes
//   int:       4 bytes
//   long:      8 bytes
//   long long: 8 bytes
//   float:     4 bytes
//   double:    8 bytes
//   int8_t:    1 bytes
//   int16_t:   2 bytes
//   int32_t:   4 bytes
//   int64_t:   8 bytes
//   size_t:    8 bytes

// YOUR CODE HERE
#include <iostream>
#include <cstdint>



int main() {


	// char
	std::cout << "char:      " << sizeof(char) << " bytes" << std::endl;
	std::cout << "bool:      " << sizeof(bool) << " bytes" << std::endl;
	std::cout << "short:     " << sizeof(short) << " bytes" << std::endl;
	std::cout << "int:       " << sizeof(int) << " bytes" << std::endl;
	std::cout << "long:      " << sizeof(long) << " bytes" << std::endl;
	std::cout << "long long: " << sizeof(long long) << " bytes" << std::endl;
	std::cout << "float:     " << sizeof(float) << " bytes" << std::endl;
	std::cout << "double:    " << sizeof(double) << " bytes" << std::endl;
	std::cout << "int8_t:    " << sizeof(int8_t) << " bytes" << std::endl;
	std::cout << "int16_t:   " << sizeof(int16_t) << " bytes" << std::endl;
	std::cout << "int32_t:   " << sizeof(int32_t) << " bytes" << std::endl;
	std::cout << "int64_t:   " << sizeof(int64_t) << " bytes" << std::endl;
	std::cout << "size_t:    " << sizeof(size_t) << " bytes" << std::endl;



	// remember the return 0 is implicit
}