// Exercise 1: Shape Structs
//
// Task: Model geometric shapes as structs with methods.
//
// Define the following structs:
//
//   struct Circle {
//       double radius;
//       double area() const;
//       double perimeter() const;
//       void print() const;  // "Circle(r=5.0): area=78.54, perimeter=31.42"
//   };
//
//   struct Rectangle {
//       double width, height;
//       double area() const;
//       double perimeter() const;
//       bool is_square() const;
//       void print() const;
//   };
//
//   struct Triangle {
//       double a, b, c;  // side lengths
//       double area() const;       // use Heron's formula
//       double perimeter() const;
//       bool is_valid() const;     // triangle inequality
//       void print() const;
//   };
//
// Heron's formula for triangle area:
//   s = (a + b + c) / 2
//   area = sqrt(s * (s-a) * (s-b) * (s-c))
//
// Requirements:
//   - Use constexpr for PI
//   - Use member initializer lists for constructors
//   - Mark all non-modifying methods const
//   - Use <cmath> for sqrt
//   - Use std::fixed and std::setprecision(2) for output
//
// In main():
//   - Create one of each shape
//   - Call print() on each
//   - Create a Circle using C++20 designated initializers:
//       Circle c{.radius = 10.0};
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_shapes.cpp

// YOUR CODE HERE
