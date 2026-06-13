// Exercise 4: Pattern Printing
//
// Task: Print the following patterns using nested loops. Ask the user
//       for the size (number of rows) for each.
//
// Pattern A — Right triangle:
//   *
//   **
//   ***
//   ****
//   *****
//
// Pattern B — Inverted right triangle:
//   *****
//   ****
//   ***
//   **
//   *
//
// Pattern C — Centered pyramid:
//       *    i = 0  num_stars = 1   space = 4 on each side
//      ***   i = 1  num_stars = 3   space = 3
//     *****  i = 2  num_stars = 5   space = 2
//    *******
//   *********
//
// Requirements:
//   - Use nested for loops
//   - Read the size from the user once, use it for all three patterns
//   - Print a blank line between patterns
//   - For the pyramid, you'll need to print spaces before the stars
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_patterns.cpp

// YOUR CODE HERE
#include<iostream>



int main() {

	int num_rows;


	// Pattern A
	std::cout << "Enter a number of rows for the pattern: ";
	std::cin >> num_rows;

	for (int i = 1; i <= num_rows; i++) {
		// for each row print the pattern
		for (int y = 0; y < i; y++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;


	
	// Pattern B
	for (int i = num_rows; i > 0; i--) {
		// for each row print the pattern
		// for each row print the pattern
		for (int y = 0; y < i; y++) {
			std::cout << "*";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;


	int padding = num_rows - 1;
	int num_stars;

	// Pattern C
	for (int i = 0; i < num_rows; i++) {
		// number of stars for row i
		num_stars = (2 * i) + 1;

		// print the padding
		for (int y = 0; y < padding; y ++) {
			std::cout << " ";
		}

		// print the stars
		for (int y = 0; y < num_stars; y ++) {
			std::cout << "*";
		}

		// print the padding
		for (int y = 0; y < padding; y ++) {
			std::cout << " ";
		}

		std::cout << std::endl;

		padding -= 1;
	}
	



}
