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
