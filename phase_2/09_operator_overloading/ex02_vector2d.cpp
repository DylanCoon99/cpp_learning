// Exercise 2: Vector2D Class
//
// Task: Build a complete 2D vector class with all common operators.
//       Expand on the Vec2 from step 08.
//
// Class definition:
//
//   class Vector2D {
//   public:
//       Vector2D(double x = 0.0, double y = 0.0);
//
//       // Getters
//       double x() const;
//       double y() const;
//       double magnitude() const;       // sqrt(x*x + y*y)
//       Vector2D normalized() const;    // unit vector (magnitude 1)
//
//       // Arithmetic
//       Vector2D& operator+=(const Vector2D& rhs);
//       Vector2D& operator-=(const Vector2D& rhs);
//       Vector2D& operator*=(double scalar);    // scalar multiply
//       Vector2D& operator/=(double scalar);    // scalar divide
//
//       Vector2D operator+(const Vector2D& rhs) const;
//       Vector2D operator-(const Vector2D& rhs) const;
//       Vector2D operator*(double scalar) const;
//       Vector2D operator/(double scalar) const;
//       Vector2D operator-() const;             // negate
//
//       // Dot product
//       double dot(const Vector2D& rhs) const;
//
//       // Comparison
//       bool operator==(const Vector2D& rhs) const;
//       bool operator!=(const Vector2D& rhs) const;
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
//
//       // Allow: 2.0 * vec  (scalar on the left side)
//       friend Vector2D operator*(double scalar, const Vector2D& v);
//   };
//
// Requirements:
//   - For == comparison with doubles, use an epsilon:
//       constexpr double EPSILON = 1e-9;
//       return std::abs(x_ - rhs.x_) < EPSILON && ...
//   - normalized() should handle zero vector (return zero vector, don't divide by 0)
//   - The friend operator* allows: 2.0 * vec (not just vec * 2.0)
//   - Stream format: "(3.5, -2.1)"
//
// In main():
//   - Create vectors, test all arithmetic
//   - Test dot product: (1,0) dot (0,1) should be 0
//   - Test normalization
//   - Test scalar multiplication from both sides: vec * 2 and 2 * vec
//   - Print using <<
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_vector2d.cpp

// YOUR CODE HERE
#include <iostream>
#include <cmath>
#include <iomanip>


class Vector2D {

public:
	Vector2D(double x = 0.0, double y = 0.0) : x_(x), y_(y) {};

	// Getters
	double x() const {
		return x_;
	}

	double y() const {
		return y_;
	}

	double magnitude() const {
		// sqrt(x*x + y*y)
		return std::sqrt((x_ * x_) + (y_ * y_));
	}

	Vector2D normalized() const {
		// unit vector (magnitude 1)
		double mag = magnitude();
		return mag != 0 ? Vector2D(x_ / mag, y_ / mag) : Vector2D();
	}

	// Arithmetic
	Vector2D& operator+=(const Vector2D& rhs) {
		x_ += rhs.x_;
		y_ += rhs.y_;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& rhs) {
		x_ -= rhs.x_;
		y_ -= rhs.y_;
		return *this;
	}

	Vector2D& operator*=(double scalar) {
		// scalar multiply
		x_ *= scalar;
		y_ *= scalar;
		return *this;
	}

	Vector2D& operator/=(double scalar) {
		// scalar divide
		x_ /= scalar;
		y_ /= scalar;
		return *this;
	}

	Vector2D operator+(const Vector2D& rhs) const {
		Vector2D result = rhs;
		result += *this;
		return result;
	}

	Vector2D operator-(const Vector2D& rhs) const {
		Vector2D result = *this;
		result -= rhs;
		return result;
	}

	Vector2D operator*(double scalar) const {
		Vector2D result = *this;
		result *= scalar;
		return result;
	}

	Vector2D operator/(double scalar) const {
		Vector2D result = *this;
		result /= scalar;
		return result;
	}

	Vector2D operator-() const {
		return Vector2D(x_ * -1, y_ * -1);
	}

	// Dot product
	double dot(const Vector2D& rhs) const {
		return (x_ * rhs.x_) + (y_ * rhs.y_);
	}

	// Comparison
	bool operator==(const Vector2D& rhs) const {
		constexpr double EPSILON = 1e-9;
		bool x_equals = std::abs(x_ - rhs.x_) < EPSILON;
		bool y_equals = std::abs(y_ - rhs.y_) < EPSILON;

		return x_equals && y_equals;
	}

	bool operator!=(const Vector2D& rhs) const {
		return !(*this == rhs);

	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
		//"(3.5, -2.1)"
		os << "(" << std::fixed << std::setprecision(2) << std::to_string(v.x_) << ", " << std::to_string(v.y_) << ")" << std::endl;
    	return os; 
	}

	// Allow: 2.0 * vec  (scalar on the left side)
	friend Vector2D operator*(double scalar, const Vector2D& v) {
		return Vector2D(scalar * v.x_, scalar * v.y_);
	}

private:
	double x_, y_;

};


int main() {

	Vector2D v1(2.0, 5.0);
	Vector2D v2(3.0, -1.0);

	// Arithmetic
	std::cout << "v1: " << v1;
	std::cout << "v2: " << v2;
	std::cout << "v1 + v2: " << v1 + v2;
	std::cout << "v1 - v2: " << v1 - v2;
	std::cout << "v1 * 3: " << v1 * 3.0;
	std::cout << "v1 / 2: " << v1 / 2.0;
	std::cout << "-v1: " << -v1;

	// Scalar from both sides
	std::cout << "2 * v2: " << 2.0 * v2;
	std::cout << "v2 * 2: " << v2 * 2.0;

	// Dot product
	Vector2D i(1.0, 0.0);
	Vector2D j(0.0, 1.0);
	std::cout << "i dot j: " << i.dot(j) << std::endl;
	std::cout << "v1 dot v2: " << v1.dot(v2) << std::endl;

	// Magnitude and normalization
	std::cout << "v1 magnitude: " << v1.magnitude() << std::endl;
	std::cout << "v1 normalized: " << v1.normalized();
	std::cout << "normalized magnitude: " << v1.normalized().magnitude() << std::endl;

	// Zero vector normalization
	Vector2D zero;
	std::cout << "zero normalized: " << zero.normalized();

	// Comparison
	std::cout << "v1 == v1: " << (v1 == v1 ? "true" : "false") << std::endl;
	std::cout << "v1 != v2: " << (v1 != v2 ? "true" : "false") << std::endl;

	// Compound assignment
	Vector2D v3(1.0, 1.0);
	v3 += v1;
	std::cout << "v3 after += v1: " << v3;
	v3 *= 2.0;
	std::cout << "v3 after *= 2: " << v3;

}
