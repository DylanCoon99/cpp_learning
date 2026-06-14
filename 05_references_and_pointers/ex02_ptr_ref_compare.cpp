// Exercise 2: Pointers vs. References Side-by-Side
//
// Task: Implement the same operations using both pointers and references
//       to see the syntactic and behavioral differences.
//
// Part A — Swap:
//   Write two versions of swap:
//     void swap_ptr(int* a, int* b)   — swap using pointers
//     void swap_ref(int& a, int& b)   — swap using references
//   Call both from main and print results.
//   Note the difference at the call site: swap_ptr(&x, &y) vs swap_ref(x, y)
//
// Part B — Find in array:
//   Write two versions:
//     int* find_ptr(int* arr, int size, int target)
//       — returns pointer to element, or nullptr if not found
//     int& find_ref(std::vector<int>& v, int target, bool& found)
//       — returns reference to element, uses bool to signal not-found
//       — if not found, return v[0] as a dummy (there's no "null reference")
//
//   This demonstrates WHY pointers are better when "not found" is possible:
//   pointers can be nullptr, references can't.
//
// Part C — Optional modification:
//   Write a function:
//     void maybe_double(int* p)
//   If p is not nullptr, double the value it points to. If null, do nothing.
//   This is a natural use of pointers — the null case is meaningful.
//   (You can't write this with a reference — it can't be null.)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_ptr_ref_compare.cpp

// YOUR CODE HERE
#include <iostream>


void swap_ptr(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}


void swap_ref(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}


int* find_ptr(int* arr, int size, int target) {

	int* ptr = nullptr;

	for (int i = 0; i < size; ++i) {
		if (arr[i] == target) {
			return &arr[i];
		}
	}


	return ptr;

}



int& find_ref(std::vector<int>& v, int target, bool& found) {

	for (int& n: v) {
		if (n == target) {
			found = true;
			return n;
		}
	}

	return v[0];

}


void maybe_double(int* p) {

	if (p != nullptr) {
		*p *= 2;
	}

}


int main() {

	// Part A
	int a = 5;
	int b = 7;

	swap_ptr(&a, &b);
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;

	// reset the values of a and b
	a = 5;
	b = 7;

	int& r1 = a;
	int& r2 = b;

	swap_ref(a, b);
	std::cout << "r1: " << r1 << std::endl;
	std::cout << "r2: " << r2 << std::endl;

	// Part B
	int arr[5] = {2, 4, 6, 8, 10};
	std::vector<int> v1 = {2, 4, 6, 8, 10};

	bool found = false; 
	int* ret1 = find_ptr(arr, 5, 8);
	find_ref(v1, 8, found);

	std::cout << "ret1: " << *ret1 << std::endl;
	std::cout << "ret2: " << (found ? "found" : "not found") << std::endl;

	// Part C

	int n = 5;

	maybe_double(&n);

	std::cout << "n: " << n << std::endl;

	int* np = nullptr;

	maybe_double(np);

	std::cout << "np: " << np << std::endl;




}