// Exercise 1: Function Templates
//
// Task: Write generic functions that work with any type.
//
// Part A — Basic function templates:
//   Write:
//     template <typename T>
//     void my_swap(T& a, T& b);          // swap two values
//
//     template <typename T>
//     T my_min(T a, T b);                // return the smaller
//
//     template <typename T>
//     T my_max(T a, T b);                // return the larger
//
//     template <typename T>
//     T my_clamp(T value, T low, T high); // clamp value to [low, high]
//
//   Test each with int, double, and std::string.
//   Note: std::string supports < and > (lexicographic), so min/max/clamp
//   all work on strings out of the box.
//
// Part B — Print array:
//   Write:
//     template <typename T>
//     void print_array(const T* arr, int size);
//
//     template <typename T>
//     void print_vector(const std::vector<T>& v);
//
//   Test with int[], double[], vector<int>, vector<string>.
//
// Part C — Two type parameters:
//   Write:
//     template <typename T, typename U>
//     auto convert(T value) -> U;
//   That converts between types using static_cast:
//     double d = convert<int, double>(42);
//
//   Write:
//     template <typename T, typename U>
//     bool is_equal(const T& a, const U& b);
//   That compares two potentially different types:
//     is_equal(42, 42.0);    // true
//     is_equal(42, 43);      // false
//
// Part D — Non-type template parameter:
//   Write:
//     template <typename T, int N>
//     T array_sum(const T (&arr)[N]);
//   This takes a reference to a C-style array of known size N.
//   The compiler deduces N from the array size. Test with:
//     int nums[] = {1, 2, 3, 4, 5};
//     std::cout << array_sum(nums);   // 15 — N deduced as 5
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_function_templates.cpp

// YOUR CODE HERE
#include <iostream>
#include <string>

// Part A — Basic function templates:
template <typename T>
void my_swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}


template <typename T>
T my_min(T a, T b) {
	return (a < b ? a : b);
}


template <typename T>
T my_max(T a, T b) {
	return (a > b ? a : b);
}


template <typename T>
T my_clamp(T value, T low, T high) {

	T ret = (value > high ? high : (value < low ? low : value));

	return ret;
}



// Part B — Print array:
template <typename T>
void print_array(const T* arr, int size) {
	std::cout << "[ ";
	for (int i = 0; i < size; ++i ) {
		std::cout << arr[i] << " ";
	}
	std::cout << "]" << std::endl;
}


template <typename T>
void print_vector(const std::vector<T>& v) {
	std::cout << "[ ";
	for (auto& elem : v)  {
		std::cout << elem << " ";
	}
	std::cout << "]" << std::endl;
}


// Part C — Two type parameters:
template <typename T, typename U>
auto convert(T value) -> U {
	return static_cast<U>(value);
}

template <typename T, typename U>
bool is_equal(T a, U b) {
	return a == b;
}


// Part D — Non-type template parameter:
template <typename T, int N>
T array_sum(const T (&arr)[N]) {
	T s = 0;
	for (int i = 0; i < N; ++i) {
		s += arr[i];
	}
	return s;
}



int main() {

	//  Part A Test each with int, double, and std::string.

	{
		// int swap
		int a = 5;
		int b = 4;
		std::cout << "Before swap" << std::endl;
		std::cout << "a: " << a << "    b: " << b << std::endl;
		my_swap(a, b);
		std::cout << "a: " << a << "    b: " << b << std::endl;
		std::cout << std::endl;

		// int min max		
		std::cout << "my_min(a, b) = " << my_min(a, b) << "    my_max(a, b)=" << my_max(a, b) << std::endl;
		std::cout << std::endl;

		// int clamp
		std::cout << "expecting 100: " << my_clamp(100, 50, 150) << std::endl;  // -> 100
		std::cout << "expecting 150: " << my_clamp(200, 50, 150) << std::endl;  // -> 150
		std::cout << "expecting 50: " << my_clamp(25, 50, 150) << std::endl;  // -> 50
	}

	{
		// double swap
		double a = 5.5;
		double b = 6.7;
		std::cout << "Before swap" << std::endl;
		std::cout << "a: " << a << "    b: " << b << std::endl;
		my_swap(a, b);
		std::cout << "a: " << a << "    b: " << b << std::endl;
		std::cout << std::endl;

		// double min max
		std::cout << "my_min(a, b) = " << my_min(a, b) << "    my_max(a, b)=" << my_max(a, b) << std::endl;
		std::cout << std::endl;

		// doubles clamp
		std::cout << "expecting 100.34: " << my_clamp(100.34, 50.231, 150.37) << std::endl;  // -> 100.24
		std::cout << "expecting 150.232: " << my_clamp(200.230, 50.232, 150.232) << std::endl;  // -> 150
		std::cout << "expecting 50.232: " << my_clamp(25.232, 50.232, 150.89) << std::endl;  // -> 50
	}


	{
		// string swap
		std::string a = "string 1";
		std::string b = "string 2";
		std::cout << "Before swap" << std::endl;
		std::cout << "a: " << a << "    b: " << b << std::endl;
		my_swap(a, b);
		std::cout << "a: " << a << "    b: " << b << std::endl;
		std::cout << std::endl;

		// string min max
		std::cout << "my_min(a, b) = " << my_min(a, b) << "    my_max(a, b)=" << my_max(a, b) << std::endl;
		std::cout << std::endl;

		// string clamp (lexicographic: "banana" is between "apple" and "mango")
		std::string low = "apple";
		std::string high = "mango";
		std::cout << "expecting banana: " << my_clamp(std::string("banana"), low, high) << std::endl;
		std::cout << "expecting mango: " << my_clamp(std::string("zebra"), low, high) << std::endl;
		std::cout << "expecting apple: " << my_clamp(std::string("aardvark"), low, high) << std::endl;

	}


	//  Part B Test with int[], double[], vector<int>, vector<string>.
	{
		// int[]
		int arr[] = {1, 2, 3, 4};
		print_array(arr, 4);
	}

	{
		// double[]
		double arr[] = {1.4, 2.7, 3.3, 4.9};
		print_array(arr, 4);
	}

	{
		// vector<int>[]
		std::vector<int> v = {1, 2, 3, 4, 5};
		print_vector(v);
	}

	{
		// vector<std::string>[]
		std::vector<std::string> v = {"Hello", "my", "name", "is", "..."};
		print_vector(v);
	}


	// Part C
	{
		double d = convert<int, double>(42);
		std::cout << "int 42 to double: " << d << std::endl;

		int i = convert<double, int>(3.99);
		std::cout << "double 3.99 to int: " << i << std::endl;

		float f = convert<int, float>(7);
		std::cout << "int 7 to float: " << f << std::endl;

		long l = convert<int, long>(100);
		std::cout << "int 100 to long: " << l << std::endl;
	}

	// Part D
	int nums[] = {1, 2, 3, 4, 5};
	std::cout << array_sum(nums);
	

}