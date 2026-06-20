// Exercise 4: BigInt — Arbitrary Precision Integer
//
// Task: Build a class that can hold integers larger than any built-in type.
//       Store digits in a vector and implement addition/comparison.
//
// Class definition:
//
//   class BigInt {
//   public:
//       BigInt();                          // default: 0
//       BigInt(long long value);           // from integer
//       explicit BigInt(const std::string& str);  // from string: "12345678901234567890"
//
//       // Arithmetic
//       BigInt& operator+=(const BigInt& rhs);
//       BigInt operator+(const BigInt& rhs) const;
//
//       // Comparison
//       bool operator==(const BigInt& rhs) const;
//       bool operator!=(const BigInt& rhs) const;
//       bool operator<(const BigInt& rhs) const;
//       bool operator>(const BigInt& rhs) const;
//
//       // Increment
//       BigInt& operator++();       // pre
//       BigInt operator++(int);     // post
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const BigInt& n);
//
//   private:
//       std::vector<int> digits_;   // stored in REVERSE order (ones place first)
//       bool negative_;
//
//       void remove_leading_zeros();
//   };
//
// Storing digits in reverse order makes addition simpler — you iterate
// from index 0 (ones place) and carry forward.
//
// Addition algorithm (for non-negative numbers):
//   carry = 0
//   for each position i:
//       sum = a.digits[i] + b.digits[i] + carry
//       result.digits[i] = sum % 10
//       carry = sum / 10
//   if carry > 0: append carry
//
// Requirements:
//   - Handle positive numbers (negative is bonus)
//   - String constructor should validate input (digits only, optional leading '-')
//   - remove_leading_zeros() cleans up after operations
//   - Comparison: compare digit by digit from most significant
//   - Stream output: print digits in correct (forward) order
//
// In main():
//   - Create BigInts from integers and strings
//   - Add two large numbers that overflow long long:
//       BigInt a("99999999999999999999");
//       BigInt b("1");
//       std::cout << a + b;  // "100000000000000000000"
//   - Test comparisons
//   - Test pre/post increment
//   - Add several numbers in a chain: a + b + c
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_bigint.cpp

// YOUR CODE HERE
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>


class BigInt {
public:
	BigInt() {
		// default: 0
		digits_.push_back(0);
	}                
	BigInt(long long value) {
		// from integer
		negative_ = (value < 0) ? true : false;


		long long v = std::abs(value);
		// use % to get the least significant digit
		// use / (integer division) to reassign value of v
		while (v != 0) {
			digits_.push_back(v % 10);
			v /= 10;
		}
	}
	explicit BigInt(const std::string& str) {
		// from string: "12345678901234567890"
		char ch;
		for (int i = str.size() - 1; i >= 0; --i) {
			ch = str[i];
			if (std::isdigit(ch)) {
				digits_.push_back(ch - '0');
			} else {
				if (ch == '-' && i == 0) {
					negative_ = true;
				}
				else {
					throw std::runtime_error("String must consist of only digits!");
				}
			}
		}

	}

	// Arithmetic
	BigInt& operator+=(const BigInt& rhs) {                                                                                                       
		int carry = 0;                                                                                                                                                               
		int max_size = std::max(digits_.size(), rhs.digits_.size());
                                                                                 
		for (int i = 0; i < max_size; ++i) {
			int a = (i < static_cast<int>(digits_.size())) ? digits_[i] : 0;                                                                                                           
			int b = (i < static_cast<int>(rhs.digits_.size())) ? rhs.digits_[i] : 0;
			int sum = a + b + carry;                                                                                                   

			if (i < static_cast<int>(digits_.size())) {                                                                                                                          
			  digits_[i] = sum % 10;                                                                                               
			} else {                                                                                                                        
			  digits_.push_back(sum % 10);
			}                                                                                                                                        
			                                                                                                                                                                       
			carry = sum / 10;
		}

		if (carry > 0) {
			digits_.push_back(carry);
		}                                                                                                                                               

		return *this;                                                                                                                                   
  }              

	BigInt operator+(const BigInt& rhs) const {
		BigInt result = *this;
		result += rhs;
		return result;
	}

	// Comparison
	bool operator==(const BigInt& rhs) const {
		if (digits_.size() == rhs.digits_.size()) {
			// check to see if the digits are the same
			for (int i = 0; i < static_cast<int>(digits_.size()); ++i) {
				if (digits_[i] != rhs.digits_[i]) {
					return false;
				}
			}
		} else {
			return false;
		}
		return true;
	}

	bool operator!=(const BigInt& rhs) const {
		return !(*this == rhs);
	}

	bool operator<(const BigInt& rhs) const {
		// this < rhs ?
		if (digits_.size() == rhs.digits_.size() - 1) {
			// check the values
			for (int i = digits_.size(); i >= 0; --i) {
				if (digits_[i] > rhs.digits_[i]) {
					return false;
				} else if (digits_[i] < rhs.digits_[i]) {
					return true;
				}
			}
		} else if (digits_.size() < rhs.digits_.size()) {
			return true;
		}

		return false;
	}

	bool operator>(const BigInt& rhs) const {
		// this > rhs ?
		if (digits_.size() == rhs.digits_.size()) {
			// check the values
			for (int i = digits_.size() - 1; i >= 0; --i) {
				if (digits_[i] > rhs.digits_[i]) {
					return true;
				} else if (digits_[i] < rhs.digits_[i]) {
					return false;
				}
			}
		} else if (digits_.size() > rhs.digits_.size()) {
			return true;
		}
		return false;
	}

	// Increment
	BigInt& operator++() {
		// pre -> increment then return
		*this += BigInt("1");
		return *this;
	}

	BigInt operator++(int) {
		// post -> return then increment
		BigInt result = *this;
		*this+=BigInt("1");
		return result;
	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const BigInt& n) {
		std::string str;

		for (int i = static_cast<int>(n.digits_.size() - 1); i >= 0; --i) {
			str += std::to_string(n.digits_[i]);
		}

		os << str << std::endl;
		return os;
	}

private:
	std::vector<int> digits_;   // stored in REVERSE order (ones place first)
	bool negative_;

	void remove_leading_zeros();
};




int main() {

	// - Create BigInts from integers and strings
	BigInt n1 = BigInt(123456789);
	BigInt a("99999999999999999999");
	BigInt b("1");
	std::cout << a + b;

	// - Add two large numbers that overflow long long:
	//  BigInt a("99999999999999999999");
	//  BigInt b("1");
	//  std::cout << a + b;  // "100000000000000000000"
	// - Test comparisons
	// - Test pre/post increment
	// - Add several numbers in a chain: a + b + c

}