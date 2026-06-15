// Exercise 5: Function Pointers
//
// In C++ (like C), functions can be passed as arguments via function pointers.
// This is the foundation for callbacks, and later we'll replace these with
// lambdas and std::function (step 16). For now, use raw function pointers.
//
// Task:
//
// Part A: Write an apply function:
//   int apply(int a, int b, int (*op)(int, int))
//   It calls op(a, b) and returns the result.
//
//   Write add, subtract, multiply functions that match the signature.
//   In main(), call apply with each operation.
//
// Part B: Write a transform function:
//   void transform(std::vector<int>& v, int (*fn)(int))
//   It applies fn to every element of v in-place.
//
//   Write square and negate functions.
//   In main(), create a vector, transform it with square, print it.
//   Then transform it with negate, print it.
//
// Part C: Write a function that returns a function pointer:
//   typedef int (*MathOp)(int, int);
//     — or —
//   using MathOp = int (*)(int, int);    // modern C++ style, preferred
//
//   MathOp get_operation(char op)
//   Returns the appropriate function pointer for '+', '-', or '*'.
//
//   In main(), ask the user for an operator and two numbers, use
//   get_operation to get the right function, then call it.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_higher_order.cpp

// YOUR CODE HERE
#include <iostream>
#include<vector>


void print_info(const std::vector<int>& v) {

	for (int n: v) {
		std::cout << n << " ";
	}

	std::cout << std::endl;

}


// Part A 
int add(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}

int mult(int a, int b) {
	return a * b;
}

int apply(int a, int b, int (*op)(int, int)) {
	return op(a, b);
} 



// Part B

int square(int a) {
	return a * a;
}

int negate(int a) {
	return a * -1;
}

void transform(std::vector<int>& v, int (*fn)(int)) {


	for (int& n : v) {
		n = fn(n);
	}

}


// Part C
using MathOp = int (*)(int, int);

MathOp get_operation(char op) {

	switch (op) {
	case '+':
		return &add;
	case '-':
		return &sub;
	case '*':
		return &mult;
	default:
		return (MathOp)nullptr;
	}
}



int main() {


	int a = 5;
	int b = 7;

	std::cout << "add: " << apply(a, b, add) << std::endl;
	std::cout << "sub: " << apply(a, b, sub) << std::endl;
	std::cout << "mult: " << apply(a, b, mult) << std::endl;


	std::vector<int> v = {1, 2, 3, 4, 5};
	print_info(v);
	transform(v, square);
	print_info(v);
	transform(v, negate);
	print_info(v);

	int num1, num2;
	char op;
	MathOp fn;

	std::cout << "Enter 2 numbers: ";
	std::cin >> num1 >> num2;

	std::cout << "Choose an operation (+, -, or *): ";
	std::cin >> op;

	fn = get_operation(op);

	std::cout << "Result: " << fn(num1, num2) << std::endl;




}