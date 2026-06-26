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
#include <algorithm>
#include <future>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>


constexpr double PI = 3.14;


class Shape {

public:
	// virtual methods
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual std::string type() const = 0;
	virtual void print() const {
		// default: prints type, area, perimeter
		std::cout << "Type: " << type() << std::endl;
		std::cout << "Area: " << area() << std::endl;
		std::cout << "Perimeter: " << perimeter() << std::endl;
	}

	virtual ~Shape() = default;

};



class Circle : public Shape {

public:
	// Constructor
	explicit Circle(double r) : radius_(r) {}

	double area() const override {
		return PI * radius_ * radius_;
	}

	double perimeter() const override {
		return 2 * PI * radius_;
	}

	std::string type() const override {
		return "Circle";
	}


private:
	double radius_;
};



class Rectangle : public Shape {

public:
		// Constructor
	Rectangle(double l, double w) : length_(l), width_(w) {}

	double area() const override {
		return length_ * width_;
	}

	double perimeter() const override {
		return 2 * (length_ + width_);
	}

	std::string type() const override {
		return "Rectangle";
	}


private:
	double length_; double width_;


};



class Triangle : public Shape {

public:

	Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

	double area() const override {
		double s = (a_ + b_ + c_) / 2;
		return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
	}

	double perimeter() const override {
		return a_ + b_ + c_;
	}

	std::string type() const override {
		return "Triangle";
	}


private:
	double a_; double b_; double c_;

};


// Make shape function
std::unique_ptr<Shape> make_shape(double radius) {
	return std::make_unique<Circle>(radius);
}


std::unique_ptr<Shape> make_shape(double length, double width) {
	return std::make_unique<Rectangle>(length, width);

}


std::unique_ptr<Shape> make_shape(double a, double b, double c) {
	return std::make_unique<Triangle>(a, b, c);
}



// Transfer ownership
void add_to_collection(std::vector<std::unique_ptr<Shape>>& v, std::unique_ptr<Shape> shape) {
	v.push_back(std::move(shape));
}



// Borrowing
void print_shape_info(const Shape& s) {
	s.print();
}


int main() {

	// Part A — vector of unique_ptr<Shape>
	{
		// block scoped
		std::vector<std::unique_ptr<Shape>> shapes;
		shapes.push_back(std::make_unique<Circle>(5.0));
		shapes.push_back(std::make_unique<Rectangle>(5.0, 2.5));
		shapes.push_back(std::make_unique<Triangle>(4, 5, 6));

		for (auto& shape : shapes) {
			shape->print();
		}

		Shape* largest_shape = nullptr;
		double largest_area = 0.0;

		for (auto& shape : shapes) {
			if (shape->area() > largest_area) {
				largest_area = shape->area();
				largest_shape = shape.get();
			}
		}

		// print the largest shape
		std::cout << "Largest Shape: " << std::endl;
		largest_shape->print();
	}

	// Part B — Factory function:
	{
		auto circle = make_shape(5.0);
		std::cout << "Circle area: " << circle->area() << std::endl;
	
		auto rectangle = make_shape(5.0, 2.5);
		std::cout << "Rectangle area: " << rectangle->area() << std::endl;
	
		auto triangle = make_shape(3.0, 4.0, 5.0);
		std::cout << "Triangle area: " << triangle->area() << std::endl;
	}

	// Part C — Transfer ownership:
	{
		// create some shapes
		auto circle = make_shape(5.0);
		auto rectangle = make_shape(5.0, 2.5);
		auto triangle = make_shape(3.0, 4.0, 5.0);

		std::vector<std::unique_ptr<Shape>> my_shapes;

		add_to_collection(my_shapes, std::move(circle));
		add_to_collection(my_shapes, std::move(rectangle));
		add_to_collection(my_shapes, std::move(triangle));


		for (auto& shape : my_shapes) {
			shape->print();
		}
	}

	// Part D — Borrowing:
	auto circle = make_shape(5.0);
	print_shape_info(*circle);


}