// Exercise 3: Const Correctness
//
// Task: Practice all the const + pointer/reference combinations.
//
// Part A — Const pointer declarations:
//   Create an int x = 42 and demonstrate each of these four:
//     int* p1              — mutable pointer to mutable int
//     const int* p2        — mutable pointer to const int
//     int* const p3        — const pointer to mutable int
//     const int* const p4  — const pointer to const int
//
//   For each, try (and comment out the failures):
//     - Changing the pointed-to value (*p = 99)
//     - Changing the pointer itself (p = nullptr)
//   Add comments explaining which operations succeed and which fail.
//
// Part B — Const-correct function signatures:
//   Write these functions with proper const usage:
//     int sum(const std::vector<int>& v)
//       — returns sum of all elements (const ref: reads but doesn't modify)
//     void zero_out(std::vector<int>& v)
//       — sets all elements to 0 (non-const ref: modifies)
//     int count_char(const std::string& s, char c)
//       — counts occurrences of c in s
//
//   Try removing a 'const' and passing a const variable — observe the error.
//
// Part C — Const reference gotcha:
//   What does this do?
//     int x = 10;
//     const int& ref = x;
//     x = 20;
//     std::cout << ref << "\n";
//   Does ref show 10 or 20? Write the code and find out. Add a comment
//   explaining why: const on the reference means you can't modify THROUGH
//   the reference, but the underlying variable can still change.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_const_correctness.cpp

// YOUR CODE HERE
#include <iostream>
#include <vector>


void print_info(const std::vector<int>& v) {

	std::cout << "Size: " << v.size() << std::endl;

	for (int n: v) {
		std::cout << n << " ";
	}

	std::cout << std::endl;

}


int sum(const std::vector<int>& v) {

	int s = 0;

	for (const int& n: v) {
		s += n;
	}

	return s;
}


void zero_out(std::vector<int>& v) {

	for (int& n: v) {
		n = 0;
	}

}


int count_char(const std::string& s, char c) {

	int occurrences = 0;

	for (const int& n: s) {
		if (n == c) {
			occurrences += 1;
		}
	}

	return occurrences;

}


int main() {

	/*
	// Part A
	int x = 42;
	const int y = 99;
	
	// mutable pointer to an int
	int* p1 = &x;

	// mutable pointer to a constant int
	const int* p2 = &y;

	// constant pointer to a mutable int
	int* const p3 = &x;

	// constant pointer to a constant int
	const int* const p4 = &y;
	*/
	

	// Part B
	std::vector<int> v = {1, 2, 3, 4, 5, 6};
	std::vector<int> v2 = v;
	std::cout << "Sum: " << sum(v) << std::endl;
	print_info(v);

	zero_out(v2);
	print_info(v2);

	const std::string s = "hello, world!";
	std::cout << "Count: " << count_char(s, 'l') << std::endl;

	// Part C
	int x = 10;
    const int& ref = x;
    x = 20;
    std::cout << ref << "\n";

    // I think the value x will be changes on line 130 because x can still change. However, it cannot change via the reference ref


}