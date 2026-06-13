// Exercise 1: FizzBuzz
//
// Task: Print numbers 1 to 100 with the classic FizzBuzz rules:
//   - Divisible by 3 and 5: print "FizzBuzz"
//   - Divisible by 3 only:  print "Fizz"
//   - Divisible by 5 only:  print "Buzz"
//   - Otherwise:            print the number
//
// Requirements:
//   - Use a for loop
//   - Use if/else if/else
//   - One output per line
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_fizzbuzz.cpp
#include<iostream>


// YOUR CODE HERE
int main() {

	for (int i = 0; i <= 100; i++) {
		
		if ((i % 3 == 0) && (i % 5 == 0)) {
			std::cout << i << ": FizzBuzz" << std::endl;
		}
		else if (i % 3 == 0) {
			std::cout <<  i << ": Fizz" << std::endl;
		}
		else if (i % 5 == 0) {
			std::cout <<  i << ": Buzz" << std::endl;
		}
		else {
			std::cout << i << std::endl;
		}
	}


}