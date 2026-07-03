// Exercise 1: Lambda Fundamentals
//
// Task: Explore captures, mutable, closures, and std::function.
//
// Part A — Capture modes:
//   - Create variables: int x = 10, y = 20, z = 30
//   - Write a lambda that captures x by value and y by reference
//   - Call it, modify y outside, call again — observe the difference
//   - Write a lambda with [=] that uses all three
//   - Write a lambda with [&] that modifies all three
//
// Part B — mutable and closures:
//   Write a function that returns a counter lambda:
//     std::function<int()> make_counter(int start = 0);
//   Each call to the returned lambda returns the next number:
//     auto c = make_counter(10);
//     c(); // 10
//     c(); // 11
//     c(); // 12
//
//   Write a function that returns an accumulator:
//     std::function<int(int)> make_accumulator();
//   Each call adds to a running total:
//     auto acc = make_accumulator();
//     acc(5);  // 5
//     acc(3);  // 8
//     acc(10); // 18
//
// Part C — std::function storage:
//   Create a std::vector<std::function<int(int)>> of transformations:
//     - double the value
//     - square the value
//     - add 10
//     - negate
//   Apply each transformation to the number 5 and print results.
//   Then chain them: apply all transformations in sequence to a starting value.
//
// Part D — Generic lambdas:
//   Write a generic lambda:
//     auto print_twice = [](const auto& x) { ... };
//   That prints any value twice on one line separated by a space.
//   Test with int, double, string, vector (you'll need to handle vector
//   specially — or just let it fail and observe the error).
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_lambda_fundamentals.cpp

#include <iostream>
#include <functional>
#include <vector>
#include <string>

int main() {

    // YOUR CODE HERE

}
