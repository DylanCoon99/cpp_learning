// Exercise 3: Simple Calculator
//
// Task: Read two integers from the user. Print their sum, difference,
//       product, and quotient.
//
// Requirements:
//   - Use int for both numbers
//   - Handle the output format as shown below
//   - For quotient, use integer division (this is fine for now)
//   - Bonus: What happens if the user enters 0 for the second number?
//            (Just observe for now — we'll handle errors properly later)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_calculator.cpp
// Example session:
//   Enter first number: 15
//   Enter second number: 4
//   15 + 4 = 19
//   15 - 4 = 11
//   15 * 4 = 60
//   15 / 4 = 3

// YOUR CODE HERE
#include <iostream>


int main() {

	int num1;
	int num2;

	int sum;
	int diff;
	int prod;
	int quot;

	std::cout << "Enter first number: ";

	std::cin >> num1;

	std::cout << "Enter second number: ";

	std::cin >> num2;

	sum = num1 + num2;
	diff = num1 - num2;
	prod = num1 * num2;
	quot = num1 / num2;

	std::cout << num1 << " + " << num2 << " = " << sum << std::endl;
	std::cout << num1 << " - " << num2 << " = " << diff << std::endl;
	std::cout << num1 << " * " << num2 << " = " << prod << std::endl;
	std::cout << num1 << " / " << num2 << " = " << quot << std::endl;

	return 0;
}