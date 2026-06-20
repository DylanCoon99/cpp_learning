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
#include <iostream>
#include <algorithm>


class Fraction {

public:
	Fraction(int numerator, int denominator) : num_(numerator), den_(denominator) {
		simplify();
	};

	// Getters
	int numerator() {
		return num_;
	}

	int denominator() {
		return den_;
	}

	// Arithmetic (compound assignment — member functions)
	Fraction& operator+=(const Fraction& rhs) {
		//   a/b + c/d = (a*d + c*b) / (b*d)
		num_ = (num_ * rhs.den_) + (rhs.num_ * den_);
		den_ = den_ * rhs.den_;
		return *this;
	}

	Fraction& operator-=(const Fraction& rhs) {
		//   a/b - c/d = (a*d - c*b) / (b*d)
		num_ = (num_ * rhs.den_) - (rhs.num_ * den_);
		den_ = den_ * rhs.den_;
		return *this;
	}

	Fraction& operator*=(const Fraction& rhs) {
		num_ *= rhs.num_;
		den_ *= rhs.den_;
		return *this;
	}

	Fraction& operator/=(const Fraction& rhs) {
		num_ *= rhs.den_;
		den_ *= rhs.num_;
		return *this;
	}

	// Arithmetic (binary — implement in terms of compound assignment)
	Fraction operator+(const Fraction& rhs) const {
		//fraction = this + rhs
		Fraction result = Fraction(num_, den_);
		result += Fraction(rhs.num_, rhs.den_);
		return result;
	}

	Fraction operator-(const Fraction& rhs) const {
		Fraction result = Fraction(num_, den_);
		result -= Fraction(rhs.num_, rhs.den_);
		return result;
	}

	Fraction operator*(const Fraction& rhs) const {
		Fraction result = Fraction(num_, den_);
		result *= Fraction(rhs.num_, rhs.den_);
		return result;
	}

	Fraction operator/(const Fraction& rhs) const {
		Fraction result = Fraction(num_, den_);
		result /= Fraction(rhs.num_, rhs.den_);
		return result;
	}

	// Unary minus
	Fraction operator-() const {
		return Fraction(num_ * -1, den_);
	}

	// Comparison
	bool operator==(const Fraction& rhs) const {
		return (num_ == rhs.num_) && (den_ == rhs.den_);
	}

	bool operator!=(const Fraction& rhs) const {
		return !(*this == rhs);
	}

	bool operator<(const Fraction& rhs) const {
		return (static_cast<double>(num_) / den_) < (static_cast<double>(rhs.num_) < rhs.den_);
	}

	bool operator>(const Fraction& rhs) const {
		return (static_cast<double>(num_) / den_) > (static_cast<double>(rhs.num_) < rhs.den_);
	}

	bool operator<=(const Fraction& rhs) const {
		return (*this < rhs) || (*this == rhs);
	}

	bool operator>=(const Fraction& rhs) const {
		return (*this > rhs) || (*this == rhs);
	}

	// Stream output (friend)
	friend std::ostream& operator<<(std::ostream& os, Fraction& f) {
		f.simplify();
		os << f.num_ << "/" << f.den_;
    	return os; 
	}




private:
	int num_;
	int den_;

	int get_gcd(int a, int b) {
		if (b == 0) {
			return a;
		}

		return get_gcd(b, a % b);
	}

	void simplify() {
		int gcd = get_gcd(std::abs(num_), std::abs(den_));
		// std::cout << "GCD: " << gcd << std::endl;
		num_ /= gcd;
		den_ /= gcd;
	}

};



int main() {
	//   - Create fractions: 1/2, 3/4, 2/3
	Fraction fraction1 = Fraction(1, 2);
	Fraction fraction2 = Fraction(3, 4);
	Fraction fraction3 = Fraction(2, 3);
	Fraction fraction4 = Fraction(2, 3);	
	Fraction fraction5 = Fraction(4, 8);
	//   - Test all arithmetic operations, print results with <<
	// compound add
	fraction1 += fraction2;
	std::cout << fraction1 << std::endl;

	// compound sub
	fraction1 -= fraction2;
	std::cout << fraction1 << std::endl;
	// compound mult
	fraction1 *= fraction2;
	std::cout << fraction1 << std::endl;
	// compound div
	fraction1 /= fraction2;
	std::cout << fraction1 << std::endl;

	//   - Test comparisons
	std::cout << "1/2 == 3/4: " << (fraction1 == fraction2 ? "true" : "false") << std::endl;
	std::cout << "2/3 == 2/3: " << (fraction3 == fraction4 ? "true" : "false") << std::endl;
	//   - Verify simplification: Fraction(4, 8) should print as "1/2"
	std::cout << fraction5 << std::endl;
	//   - Test unary minus
	Fraction fraction6 = -fraction1;
	std::cout << fraction6 << std::endl;
	//   - Test chaining: (a + b) * c
	Fraction fraction7 = (fraction1 + fraction2) * fraction3;
	std::cout << fraction7 << std::endl;



}
