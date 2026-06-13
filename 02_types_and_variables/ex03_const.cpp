// Exercise 3: const and constexpr
//
// Task: Practice using const and constexpr.
//
// Part A:
//   - Declare a constexpr for PI (3.14159265358979)
//   - Declare a constexpr function called circle_area that takes a double
//     radius and returns the area (PI * r * r)
//   - Use it to compute the area of a circle with radius 5.0 at compile time
//   - Print the result
//
// Part B:
//   - Read a radius from the user (this is a runtime value)
//   - Pass it to your circle_area function (constexpr functions CAN be
//     called at runtime too — they just CAN'T be constexpr-evaluated
//     with runtime inputs)
//   - Print the result
//
// Part C:
//   - Try uncommenting the line that modifies a const variable.
//   - Observe the compiler error. Then re-comment it.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_const.cpp
// Example session:
//   Area of circle with radius 5.0: 78.54
//   Enter a radius: 3
//   Area of circle with radius 3: 28.27

// YOUR CODE HERE

// Part C: Uncomment the next two lines to see the compiler error, then re-comment.
// const int x = 10;
// x = 20;
