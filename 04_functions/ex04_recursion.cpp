// Exercise 4: Recursive Functions
//
// Task: Implement the following functions recursively.
//
// Part A: int factorial(int n)
//   - Return n! (e.g., factorial(5) = 120)
//   - Base case: factorial(0) = 1
//
// Part B: int fibonacci(int n)
//   - Return the nth Fibonacci number (0-indexed)
//   - fib(0)=0, fib(1)=1, fib(n)=fib(n-1)+fib(n-2)
//   - Print fib(0) through fib(15)
//
// Part C: int power(int base, int exp)
//   - Compute base^exp recursively
//   - Use the "fast exponentiation" approach:
//       power(b, 0) = 1
//       power(b, e) = power(b, e/2)^2          if e is even
//       power(b, e) = b * power(b, e/2)^2      if e is odd
//   - This runs in O(log n) instead of O(n)
//
// Part D (bonus): bool is_palindrome(const std::string& s, int left, int right)
//   - Check if a string is a palindrome recursively
//   - Provide a convenience overload: bool is_palindrome(const std::string& s)
//     that calls the three-arg version with left=0, right=s.size()-1
//
// Mark all functions [[nodiscard]] since ignoring their return value is a bug.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_recursion.cpp

// YOUR CODE HERE
