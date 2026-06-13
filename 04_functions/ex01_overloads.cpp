// Exercise 1: Function Overloading
//
// Task: Write a set of overloaded functions called "display" that handle
//       different types and argument counts.
//
// Requirements:
//   - display(int)            — prints "Integer: 42"
//   - display(double)         — prints "Double: 3.14"
//   - display(const std::string&) — prints "String: hello"
//   - display(int, int)       — prints "Two ints: 3 and 7"
//   - display(char, int)      — prints the char repeated int times
//                                e.g., display('*', 5) prints "*****"
//
// In main(), call each overload and observe the correct one being selected.
//
// Question to consider: What happens if you call display(3.14f)? Which
// overload gets called? Try it and see if the compiler warns.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_overloads.cpp

// YOUR CODE HERE
#include <iostream>	



void display(int n) {
	std::cout << "Integer: " << n << std::endl;
}

void display(double n) {
	std::cout << "Double: " << n << std::endl;

}

void display(const std::string& s) {
	std::cout << "String: " << s << std::endl;

}

void display(int n, int m) {
	std::cout << "Two ints: " << n << " and " << m << std::endl;

}

void display(char a, int n) {
	for (int i = 0; i < n; i ++) {
		std::cout << a;
	}
}

int main() {

	display(5);
	display(3.14);
	display("Hello, world!");
	display(5, 2);
	display('a', 2);

}