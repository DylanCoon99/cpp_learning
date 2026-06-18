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
