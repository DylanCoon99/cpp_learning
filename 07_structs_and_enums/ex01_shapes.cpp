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
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>


constexpr double PI = 3.14;


struct Circle {
	double radius;

	Circle(double r): radius(r) {}

	double area() const {

		return PI * radius * radius;
	}

	double perimeter() const {
		return 2 * PI * radius;
	}
	void print() const{
		std::cout << "Circle(r=" << radius << "): area=" << std::fixed << std::setprecision(2) << area() << ", perimeter=" << std::fixed << std::setprecision(2) << perimeter() << std::endl;
	}  
};


struct Rectangle {
	double width, height;

	Rectangle(double w, double h): width(w), height(h) {}

	double area() const {
		return width * height;
	}

	double perimeter() const {
		return 2 * (width + height);
	}

	bool is_square() const {
		return width == height;
	}

	void print() const {
		std::cout << "Rectangle(w=" << width << ", h=" << height << "): area=" << std::fixed << std::setprecision(2) << area() << ", perimeter=" << std::fixed << std::setprecision(2) << perimeter() << std::endl;
	}
};

struct Triangle {
	double a, b, c;  // side lengths

	Triangle(double a, double b, double c): a(a), b(b), c(c) {}

	double area() const {
		int s = (a + b + c) / 2;
		return std::sqrt(s * (s-a) * (s-b) * (s-c));
	}

	double perimeter() const {
		return a + b + c;
	}

	bool is_valid() const{
		return a + b > c && a + c > b && b + c > a;
	}

	void print() const {
		std::cout << "Triangle(a=" << a << ", b=" << b<< ", c=" << c << "): area=" << std::fixed << std::setprecision(2) << area() << ", perimeter=" << std::fixed << std::setprecision(2) << perimeter()<< ", valid=" << (is_valid() ? "true" : "false") << std::endl;
	}

};



int main() {


	Circle c = Circle(5.0);
	Rectangle r = Rectangle(4, 5);
	Triangle t = Triangle(3, 4, 5);

	c.print();
	r.print();
	t.print();




}