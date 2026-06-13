// Exercise 5: Function Pointers
//
// In C++ (like C), functions can be passed as arguments via function pointers.
// This is the foundation for callbacks, and later we'll replace these with
// lambdas and std::function (step 16). For now, use raw function pointers.
//
// Task:
//
// Part A: Write an apply function:
//   int apply(int a, int b, int (*op)(int, int))
//   It calls op(a, b) and returns the result.
//
//   Write add, subtract, multiply functions that match the signature.
//   In main(), call apply with each operation.
//
// Part B: Write a transform function:
//   void transform(std::vector<int>& v, int (*fn)(int))
//   It applies fn to every element of v in-place.
//
//   Write square and negate functions.
//   In main(), create a vector, transform it with square, print it.
//   Then transform it with negate, print it.
//
// Part C: Write a function that returns a function pointer:
//   typedef int (*MathOp)(int, int);
//     — or —
//   using MathOp = int (*)(int, int);    // modern C++ style, preferred
//
//   MathOp get_operation(char op)
//   Returns the appropriate function pointer for '+', '-', or '*'.
//
//   In main(), ask the user for an operator and two numbers, use
//   get_operation to get the right function, then call it.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_higher_order.cpp

// YOUR CODE HERE
