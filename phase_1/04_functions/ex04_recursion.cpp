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
#include <iostream>


// Part A
int factorial(int n) {

	if (n == 0 || n == 1) {
		return n;
	}
	else {
		return n * factorial(n - 1);
	}

} 


// Part B
int fibonacci(int n) {

	// base case
	if (n == 0 || n == 1) {
		return n;
	}
	else {
		return fibonacci(n - 1) + fibonacci(n - 2);
	}


}


// Part C
int power(int base, int exp) {

	if (exp == 0) {
		return 1;
	} else if (exp == 1) {
		return base;
	} else {
		return base * power(base, exp - 1);
	}

}


// Part D bonus
bool is_palindrome(const std::string& s, int left, int right) {

	while (left <= right) {
		if (s[left] != s[right]) {
			return false;
		}
		left += 1;
		right -= 1;
	}

	return true;

}


bool is_palindrome(const std::string& s) {

	return is_palindrome(s, 0, s.size()-1);
}


int main() {


	// test factorial
	std::cout << "factorial(5): " << factorial(5) << std::endl;


	// test fibonacci
	for (int i = 0; i <= 15; ++i) {
		std::cout << "Fib(" << i << "): " << fibonacci(i) << std::endl;
	}


	// test power
	std::cout << "4^3 = " << power(4, 3) << std::endl;


	std::string word1 = "hannah";  // palindrome
	std::string word2 = "racecar"; // palindrome
	std::string word3 = "phone";   // not a palindrome


	std::cout << word1 << ": " << (is_palindrome(word1) ? "true" : "false") << std::endl;
	std::cout << word2 << ": " << (is_palindrome(word2) ? "true" : "false") << std::endl;
	std::cout << word3 << ": " << (is_palindrome(word3) ? "true" : "false") << std::endl;


}