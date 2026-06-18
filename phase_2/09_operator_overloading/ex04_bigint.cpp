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
