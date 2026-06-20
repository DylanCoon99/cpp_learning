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
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

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



class Square : public Rectangle {

public: 
	explicit Square(double side) : Rectangle(side, side) {} 

};


int main() {

	/*
	//   - Create a std::vector<Shape*> with one of each shape
	Circle c = Circle(5.0);
	Rectangle r = Rectangle(2.0, 4.0);
	Triangle t = Triangle(2.0, 2.0, 2.0);
	Square s = Square(4.0);
	std::vector<Shape*> my_shapes = {&c, &r, &t, &s};
	//   - Loop through and call print() on each — polymorphism in action
	double largest_area = 0.0;
	Shape* biggest_shape;
	for (auto shape : my_shapes) {
		if (shape->area() > largest_area) {
			biggest_shape = shape;
			largest_area = shape->area();
		}
		shape->print();
	}
	//   - Find the shape with the largest area
	std::cout << "Largest Shape: ";
	biggest_shape->print();
 	*/

	/*
	// Store different derived types in one container:
	std::vector<std::unique_ptr<Shape>> shapes;  // unique_ptr — preview of step 12
	shapes.push_back(std::make_unique<Circle>(5));
	shapes.push_back(std::make_unique<Rectangle>(3, 4));
	shapes.push_back(std::make_unique<Triangle>(3, 4, 5));

	// Polymorphic call — each shape's own area() is called:
	for (const auto& s : shapes) {
	    s->print();   // calls Circle::print(), Rectangle::print(), etc.
	}
	*/

	// For now, you can use raw pointers (we'll switch to smart pointers in step 12):
	std::vector<Shape*> shapes;
	shapes.push_back(new Circle(5));
	shapes.push_back(new Rectangle(3, 4));
	shapes.push_back(new Triangle(3, 4, 5));
	// ... don't forget to delete each one when done

	double largest_area = 0.0;
	Shape* biggest_shape;
	for (auto shape : shapes) {
		if (shape->area() > largest_area) {
			biggest_shape = shape;
			largest_area = shape->area();
		}
		shape->print();
	}
	//   - Find the shape with the largest area
	std::cout << "Largest Shape: ";
	biggest_shape->print();

	for (auto& shape : shapes) {
		delete shape;
	}

}