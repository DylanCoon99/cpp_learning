// Exercise 1: Fraction Class
//
// Task: Build a Fraction class with full arithmetic operator support.
//
// Class definition:
//
//   class Fraction {
//   public:
//       Fraction(int numerator = 0, int denominator = 1);
//
//       // Getters
//       int numerator() const;
//       int denominator() const;
//
//       // Arithmetic (compound assignment — member functions)
//       Fraction& operator+=(const Fraction& rhs);
//       Fraction& operator-=(const Fraction& rhs);
//       Fraction& operator*=(const Fraction& rhs);
//       Fraction& operator/=(const Fraction& rhs);
//
//       // Arithmetic (binary — implement in terms of compound assignment)
//       Fraction operator+(const Fraction& rhs) const;
//       Fraction operator-(const Fraction& rhs) const;
//       Fraction operator*(const Fraction& rhs) const;
//       Fraction operator/(const Fraction& rhs) const;
//
//       // Unary minus
//       Fraction operator-() const;
//
//       // Comparison
//       bool operator==(const Fraction& rhs) const;
//       bool operator!=(const Fraction& rhs) const;
//       bool operator<(const Fraction& rhs) const;
//       bool operator>(const Fraction& rhs) const;
//       bool operator<=(const Fraction& rhs) const;
//       bool operator>=(const Fraction& rhs) const;
//
//       // Stream output (friend)
//       friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
//
//   private:
//       int num_;
//       int den_;
//       void simplify();  // reduce to lowest terms using GCD
//   };
//
// Requirements:
//   - Constructor should throw if denominator is 0
//   - Always store in simplified form (call simplify() after every operation)
//   - Keep denominator positive (if negative, negate both num and den)
//   - simplify() should use GCD (greatest common divisor):
//       int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
//   - Implement binary +, -, *, / in terms of +=, -=, *=, /=
//   - Implement !=, >, <=, >= in terms of == and <
//   - Stream output format: "3/4" or "-1/2" (for whole numbers: "5/1" is fine)
//
// Fraction arithmetic refresher:
//   a/b + c/d = (a*d + c*b) / (b*d)
//   a/b - c/d = (a*d - c*b) / (b*d)
//   a/b * c/d = (a*c) / (b*d)
//   a/b / c/d = (a*d) / (b*c)
//
// In main():
//   - Create fractions: 1/2, 3/4, 2/3
//   - Test all arithmetic operations, print results with <<
//   - Test comparisons
//   - Verify simplification: Fraction(4, 8) should print as "1/2"
//   - Test unary minus
//   - Test chaining: (a + b) * c
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_fraction.cpp

// YOUR CODE HERE
