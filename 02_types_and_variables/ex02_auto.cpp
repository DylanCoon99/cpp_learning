// Exercise 2: auto Type Deduction
//
// Task: Declare variables using auto and verify their types.
//
// Requirements:
//   - Declare auto variables initialized with:
//       42, 3.14, 3.14f, true, 'A', "hello"
//   - For each, print the value
//   - Use typeid(var).name() to print the compiler's internal type name
//       (requires #include <typeinfo>)
//   - Note: typeid names are compiler-specific and mangled (e.g., "i" for int
//     on GCC). That's fine — the goal is to see that different literals
//     produce different types.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_auto.cpp
// Example output (GCC):
//   42 has type: i
//   3.14 has type: d
//   3.14f has type: f
//   true has type: b
//   'A' has type: c
//   "hello" has type: PKc
//
// Question to consider: "hello" is NOT a std::string by default. What is it?
// (Hint: PKc = pointer to const char. It's a C-string literal, same as in C.)

// YOUR CODE HERE
