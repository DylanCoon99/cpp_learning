// Exercise 2: Personal Greeting
//
// Task: Ask the user for their first name, then their age.
//       Print a greeting using both.
//
// Requirements:
//   - Use std::string for the name
//   - Use int for the age
//   - Use std::cin to read input
//   - Use std::cout for output
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_greeting.cpp
// Example session:
//   What is your name? Dylan
//   How old are you? 28
//   Hello, Dylan! You are 28 years old.

// YOUR CODE HERE
#include <iostream>
#include <string>


int main() {

	std::string name;
	int age;

	std::cout << "What is your name? ";

	std::cin >> name;

	std::cout << "How old are you? ";

	std::cin >> age;

	std::cout << "Hello, " << name << "! You are " << age << " years old.";


	return 0;
}