// Exercise 3: Pass by Value, Reference, and Const Reference
//
// Task: Write three functions that demonstrate the difference.
//
// Part A: Write these three functions:
//
//   void triple_val(int x)       — multiplies x by 3 (by value)
//   void triple_ref(int& x)     — multiplies x by 3 (by reference)
//   void print_info(const std::vector<int>& v)  — prints size and all elements
//
//   In main(), demonstrate that triple_val does NOT change the original,
//   triple_ref DOES change the original, and print_info reads without copying.
//
// Part B: Write a swap function:
//   void swap(int& a, int& b)
//   Swap two integers using references. (Yes, std::swap exists — write your own.)
//
// Part C: Write a function that returns multiple values through reference params:
//   void min_max(const std::vector<int>& v, int& min_out, int& max_out)
//   Finds the minimum and maximum values in a vector and writes them to
//   the output parameters.
//
//   In main(), create a vector, call min_max, and print the results.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_pass_by.cpp
//
// Note: Returning multiple values via output parameters (Part C) is the old
// C/C++ style. Later we'll learn about std::pair, std::tuple, and structured
// bindings which are the modern way.

// YOUR CODE HERE
#include<vector>
#include<iostream>



void triple_val(int x) {
	x *= 3;
}

void triple_ref(int& x) {
	x *= 3;
}


void print_info(const std::vector<int>& v) {

	std::cout << "Size: " << v.size() << std::endl;

	for (int n: v) {
		std::cout << n << " ";
	}

}



void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}



void min_max(const std::vector<int>& v, int& min_out, int& max_out) {

	int min = v[0];
	int max = v[0];

	for (int n: v) {
		if (n < min) {
			min = n;
		}
		else if (n > max) {
			max = n;
		}
	}

	min_out = min;
	max_out = max;
}



int main() {

	// Part A
	int x = 5;
	std::cout << "Triple Value" << std::endl;
	std::cout << "Before: " << x << std::endl;
	triple_val(x);
	std::cout << "After: " << x << std::endl;
	std::cout << std::endl;

	std::cout << "Triple Reference" << std::endl;
	std::cout << "Before: " << x << std::endl;
	triple_ref(x);
	std::cout << "After: " << x << std::endl;
	std::cout << std::endl;

	std::vector<int> v = {1, 2, 3, 4, 5};
	print_info(v);


	// Part B
	int a = 5;
	int b = 4;

	std::cout << "Before swap: " << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;

	swap(a, b);

	std::cout << "After swap: " << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;


	// Part C
	int min, max;
	min_max(v, min, max);

	std::cout << "Min: " << min << std::endl;
	std::cout << "Max: " << max << std::endl;

	

}