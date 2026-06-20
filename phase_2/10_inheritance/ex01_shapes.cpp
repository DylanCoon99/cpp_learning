// Exercise 1: Shape Hierarchy
//
// Task: Build a shape class hierarchy using abstract base classes and
//       polymorphism.
//
// Define:
//
//   class Shape (abstract base):
//       virtual double area() const = 0;
//       virtual double perimeter() const = 0;
//       virtual std::string type() const = 0;
//       virtual void print() const;        // default: prints type, area, perimeter
//       virtual ~Shape() = default;
//
//   class Circle : public Shape
//       Constructor: Circle(double radius)
//       Store radius_
//
//   class Rectangle : public Shape
//       Constructor: Rectangle(double width, double height)
//       Store width_, height_
//       bool is_square() const;
//
//   class Triangle : public Shape
//       Constructor: Triangle(double a, double b, double c)
//       Store a_, b_, c_ (side lengths)
//       Validate triangle inequality in constructor (throw if invalid)
//       Use Heron's formula for area
//
//   class Square : public Rectangle
//       Constructor: Square(double side)
//       Delegates to Rectangle(side, side)
//       Overrides type() to return "Square" instead of "Rectangle"
//
// Requirements:
//   - Use override on every overridden method
//   - Use virtual destructor on base class
//   - Mark constructors explicit where appropriate (single-arg)
//
// In main():
//   - Create a std::vector<Shape*> with one of each shape
//   - Loop through and call print() on each — polymorphism in action
//   - Find the shape with the largest area
//   - Clean up (delete each pointer) — we'll fix this with smart pointers later
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_shapes.cpp

// YOUR CODE HERE
