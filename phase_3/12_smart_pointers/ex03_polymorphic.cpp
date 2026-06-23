// Exercise 3: Polymorphism with Smart Pointers
//
// Task: Refactor the shape hierarchy from step 10 to use smart pointers.
//       No more manual delete!
//
// Reuse (or redefine) from step 10:
//   class Shape (abstract base with virtual destructor)
//   class Circle : public Shape
//   class Rectangle : public Shape
//   class Triangle : public Shape
//
// Part A — vector of unique_ptr<Shape>:
//   - Create a vector<unique_ptr<Shape>>
//   - Add shapes using make_unique:
//       shapes.push_back(std::make_unique<Circle>(5.0));
//   - Loop and call print() on each — polymorphism works through smart pointers
//   - Find the largest shape by area
//   - Let the vector go out of scope — all shapes are automatically freed
//   - NO delete anywhere in your code
//
// Part B — Factory function:
//   Write:
//     std::unique_ptr<Shape> make_shape(const std::string& type, /* params */)
//   That returns the right derived type based on a string:
//     "circle" → make_unique<Circle>(r)
//     "rectangle" → make_unique<Rectangle>(w, h)
//     "triangle" → make_unique<Triangle>(a, b, c)
//     unknown → return nullptr
//
//   In main():
//     auto s = make_shape("circle", ...);
//     if (s) s->print();
//
// Part C — Transfer ownership:
//   Write:
//     void add_to_collection(std::vector<std::unique_ptr<Shape>>& v,
//                            std::unique_ptr<Shape> shape)
//   That moves a shape into the vector.
//
//   Create shapes, transfer them to a collection, print all.
//
// Part D — Borrowing:
//   Write:
//     void print_shape_info(const Shape& s)
//   That takes a reference (not a smart pointer).
//
//   Demonstrate calling it with: print_shape_info(*my_unique_ptr);
//   The function doesn't know or care that the caller uses smart pointers.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_polymorphic.cpp

// YOUR CODE HERE
