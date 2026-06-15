// Exercise 2: Number Guessing Game
//
// Task: Generate a random number between 1 and 100. Let the user guess
//       until they get it right, giving "too high" or "too low" hints.
//
// Requirements:
//   - Use a while loop (or do-while)
//   - Print how many guesses it took when they get it right
//   - Use the following for random number generation:
//
//       #include <random>
//       std::random_device rd;
//       std::mt19937 gen(rd());
//       std::uniform_int_distribution<int> dist(1, 100);
//       int secret = dist(gen);
//
//     This is the modern C++ way to generate random numbers.
//     (Don't use rand()/srand() — that's the old C way.)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_guessing.cpp
// Example session:
//   I'm thinking of a number between 1 and 100.
//   Your guess: 50
//   Too high!
//   Your guess: 25
//   Too low!
//   Your guess: 37
//   Correct! You got it in 3 guesses.

// YOUR CODE HERE
#include <random>
#include <iostream>


int main() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 100);
	int secret = dist(gen);

	int guess;
	int num_guesses = 0;

	std::cout << "I'm thinking of a number between 1 and 100." << std::endl;


	while (true) {

		// prompt user for input
		std::cout << "Your guess: ";
		std::cin >> guess;
		num_guesses += 1;

		// check the users guess
		if (guess > secret) {
			std::cout << "Too high!" << std::endl;
		}
		else if (guess < secret) {
			std::cout << "Too low!" << std::endl;
		}
		else {
			std::cout << "Correct! You got it in " << num_guesses << " guesses." << std::endl;
			break;
		}


	}

}

