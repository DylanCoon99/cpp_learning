// Exercise 1: Reference Fundamentals
//
// Task: Demonstrate how references work as aliases.
//
// Part A — Basic aliasing:
//   - Create an int variable x = 10
//   - Create a reference ref to x
//   - Modify x through ref, print both to show they're the same
//   - Print the addresses of x and ref to prove they're identical
//
// Part B — References can't be rebound:
//   - Create two ints: a = 5, b = 10
//   - Create a reference r to a
//   - Assign b to r. Print a, b, and r.
//   - Explain in a comment: did r rebind to b, or did a get b's value?
//
// Part C — Const references:
//   - Create a const reference to an int variable. Try to modify through
//     it (comment out after seeing the error).
//   - Create a const reference to a literal: const int& r = 42;
//     Print it. Note: this works because const refs extend temporary lifetime.
//   - Write a function: void print_val(const int& x) that prints x.
//     Call it with a variable, a literal, and an expression (e.g., a + b).
//     All three work because of const ref binding rules.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_ref_basics.cpp

// YOUR CODE HERE
