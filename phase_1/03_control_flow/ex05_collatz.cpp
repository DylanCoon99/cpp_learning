// Exercise 5: Collatz Conjecture
//
// The Collatz conjecture: start with any positive integer n.
//   - If n is even: n = n / 2
//   - If n is odd:  n = 3n + 1
//   Repeat until n reaches 1.
//
// Task A: Single number
//   - Read a positive integer from the user
//   - Print each step of the sequence
//   - Print how many steps it took to reach 1
//
// Task B: Range analysis
//   - For every number from 1 to 100, compute the Collatz sequence length
//   - Store the results in a std::vector<int>
//   - Use a range-based for loop to find which starting number has the
//     longest sequence
//   - Print the winner and its sequence length
//
// Requirements:
//   - Use a while loop for the Collatz sequence
//   - Use range-based for (for const auto& ...) for the analysis
//   - #include <vector> for std::vector
//   - Try using if-with-initializer somewhere:
//       if (auto len = collatz_length(n); len > max_len) { ... }
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_collatz.cpp
// Example output (Task A):
//   Enter a number: 6
//   6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
//   Steps: 8
//
// Example output (Task B):
//   Longest sequence: starting number 97 with 118 steps

// YOUR CODE HERE
#include<vector>
#include<iostream>


int collatz_length(int num) {

	int steps{0};

	while (num != 1) {

		if (num % 2 == 0) {
			num /= 2;
		}
		else {
			num = (3 * num) + 1;
		}

		steps += 1;

	}

	return steps;
}

int main() {

	// Task A
	int num;
	std::cout << "Enter a number: ";
	std::cin >> num;
	int steps = 0;


	while (num != 1) {

		std::cout << num << " -> ";

		if (num % 2 == 0) {
			num /= 2;
		}
		else {
			num = (3 * num) + 1;
		}

		steps += 1;

	}

	std::cout << "1" << std::endl;


	std::cout << "Steps: " << steps << std::endl;


	// Part B
	std::vector<int> nums(100);  // declare a vector of size 100

	// index i corresponds to collatz_number(i + 1)


	for (int i = 0; i < 100; i++) {
		nums[i] = collatz_length(i + 1);
	}

	int biggest = 0;

	// iterate over the vector with a range based for loop and find the longest
	for (int i = 0; int n: nums) {
		
		if (n > nums[biggest]) {
			biggest = i + 1;
		}

		i += 1;

	}

	std::cout << biggest << std::endl;

	std::cout << "The winner is " << biggest << " with sequence length " << nums[biggest - 1] << std::endl;

}