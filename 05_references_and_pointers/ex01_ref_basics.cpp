// Exercise 1: Reference Fundamentals
//
// Task: Demonstrate how references work as aliases.
//
// Part A — Basic aliasing:
//   - Create an int variable x = 10
//   - Create a reference ref to x
//   - Modify x through ref, print both to show they're the same
//   - Print the addresses of x and ref to prove they're identical
//
// Part B — References can't be rebound:
//   - Create two ints: a = 5, b = 10
//   - Create a reference r to a
//   - Assign b to r. Print a, b, and r.
//   - Explain in a comment: did r rebind to b, or did a get b's value?
//
// Part C — Const references:
//   - Create a const reference to an int variable. Try to modify through
//     it (comment out after seeing the error).
//   - Create a const reference to a literal: const int& r = 42;
//     Print it. Note: this works because const refs extend temporary lifetime.
//   - Write a function: void print_val(const int& x) that prints x.
//     Call it with a variable, a literal, and an expression (e.g., a + b).
//     All three work because of const ref binding rules.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_ref_basics.cpp

// YOUR CODE HERE
#include <iostream>


void print_val(const int& x) {
	std::cout << x << std::endl;
}


int main() {

	// Part A
	int x = 10;
	int& ref = x;


	ref = 20;

	std::cout << "x: " << x << std::endl;	
	std::cout << "ref: " << ref << std::endl;


	// Part B
	int a = 5;
	int b = 10;
	int& r = a;

	b = r;

	std::cout << "a: " << a << std::endl;	
	std::cout << "b: " << b << std::endl;
	std::cout << "r: " << r << std::endl;	

	a = 6;
	std::cout << std::endl;		

	std::cout << "a: " << a << std::endl;	
	std::cout << "b: " << b << std::endl;
	std::cout << "r: " << r << std::endl;	


	// the reference did not bind to b; b is just assigned to the value of r / a

	// Part C
	int z = 5;

	const int& r2 = z;

	//r2 = 6; // causes an error

	const int& r3 = 42;
	std::cout << "r3: " << r3 << std::endl;

	std::cout << std::endl;		
	// variable
	print_val(r3);
	// literal
	print_val(7);
	// expression
	print_val(r + r2);


	


}