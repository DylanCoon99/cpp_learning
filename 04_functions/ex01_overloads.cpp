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
