// Exercise 3: Menu Calculator with Switch
//
// Task: Build a simple calculator that shows a menu, reads a choice,
//       performs the operation, and loops until the user quits.
//
// Requirements:
//   - Display a menu:
//       1. Add
//       2. Subtract
//       3. Multiply
//       4. Divide
//       5. Quit
//   - Use switch to handle the choice
//   - For divide, check for division by zero and print an error
//   - Loop back to the menu after each operation (use a while loop)
//   - Use [[fallthrough]] somewhere intentionally (e.g., maybe options
//     3 and 4 share a "reading two numbers" step, or just add a comment
//     explaining where you might use it)
//   - Try the C++17 init-statement in your switch:
//       switch (int choice; std::cin >> choice, choice) { ... }
//     (This is optional — do it the normal way first if this feels weird)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_switch.cpp
// Example session:
//   === Calculator ===
//   1. Add
//   2. Subtract
//   3. Multiply
//   4. Divide
//   5. Quit
//   Choice: 1
//   Enter two numbers: 10 3
//   Result: 13
//   Choice: 4
//   Enter two numbers: 10 0
//   Error: division by zero
//   Choice: 5
//   Goodbye!

// YOUR CODE HERE
#include<iostream>

int main() {

	// display the menu
	std::cout << R"(
=== Calculator ===
1. Add
2. Subtract
3. Multiply
4. Divide
5. Quit
	)" << std::endl;

	int choice;
	int result;

	int num1;
	int num2;


	while (true) {
		std::cout << "Choice: ";
		std::cin >> choice;

		if (choice == 5) {
			break;
		}

		std::cout << "Enter two numbers: ";
		std::cin >> num1 >> num2;
		
		switch (choice) {
		case 1:
			// Add
			result = num1 + num2;
			std::cout << "Result: " << result << std::endl;
			break;
		case 2:
			// Sub
			result = num1 - num2;
			std::cout << "Result: " << result << std::endl;
			break;
		case 3:
			// Mult
			result = num1 * num2;
			std::cout << "Result: " << result << std::endl;
			break;
		case 4:
			// Divide
			if (num2 == 0) {
				std::cout << "Error: division by zero" << std::endl;
			}
			else {
				result = num1 / num2;
				std::cout << "Result: " << result << std::endl;
			}
			
			break;
		}

	}





}

