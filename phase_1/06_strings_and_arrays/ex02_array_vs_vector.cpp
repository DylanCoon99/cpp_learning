// Exercise 2: std::array vs std::vector
//
// Task: Explore the differences between fixed and dynamic arrays.
//
// Part A — std::array:
//   - Create a std::array<int, 7> with the days of the month for a week
//     (e.g., pick any 7 consecutive days)
//   - Print all elements using a range-based for loop
//   - Print the size using .size()
//   - Try accessing an out-of-bounds index with .at() — catch the
//     std::out_of_range exception:
//       try {
//           arr.at(100);
//       } catch (const std::out_of_range& e) {
//           std::cout << "Error: " << e.what() << "\n";
//       }
//   - Fill the entire array with -1 using .fill(), then print
//
// Part B — std::vector growth:
//   - Create an empty vector<int>
//   - In a loop, push_back numbers 1 through 20
//   - After each push_back, print: size, capacity, and the number added
//   - Observe when capacity jumps (the vector reallocates)
//   - What growth factor does your implementation use? (usually 2x)
//
// Part C — vector vs array as function parameters:
//   Write two functions:
//     double average(const std::array<double, 5>& arr)
//     double average(const std::vector<double>& vec)
//   - The array version only works with exactly 5 elements
//   - The vector version works with any size
//   - Call both and print results
//   - Note: this is function overloading from step 04!
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_array_vs_vector.cpp

// YOUR CODE HERE
#include <iostream>
#include <array>
#include <stdexcept>
#include <vector>


double average(const std::array<double, 5>& arr) {

	double s = 0.0;

	for (const auto& n : arr) {
		s += n;
	}


	return s / 5;
}


double average(const std::vector<double>& vec) {

	double s = 0.0;

	for (const auto& n : vec) {
		s += n;
	}

	return s / vec.size();
}


int main() {

	// Part A
	std::array<int, 7> days = {1, 2, 3, 4, 5, 6, 7};

	for (const int& i : days) {
		std::cout << i << std::endl;
	}

	std::cout << "size: " << days.size() << std::endl;

	try {
		days.at(100);
	} catch (const std::out_of_range& e) {
		std::cout << "Error: " << e.what() << "\n";
	}

	days.fill(-1);

	for (const int& i : days) {
		std::cout << i << std::endl;
	}

	// Part B
	std::vector<int> v;

	for (int i= 1; i <= 20; ++i) {
		v.push_back(i);
		std::cout << "Size:  " << v.size() << "  Capacity:  " << v.capacity() << "  Added:  " << i << std::endl;
	}

	/*
		Size:  1  Capacity:  1  Added:  1
		Size:  2  Capacity:  2  Added:  2
		Size:  3  Capacity:  4  Added:  3
		Size:  4  Capacity:  4  Added:  4
		Size:  5  Capacity:  8  Added:  5
		Size:  6  Capacity:  8  Added:  6
		Size:  7  Capacity:  8  Added:  7
		Size:  8  Capacity:  8  Added:  8
		Size:  9  Capacity:  16  Added:  9
		Size:  10  Capacity:  16  Added:  10
		Size:  11  Capacity:  16  Added:  11
		Size:  12  Capacity:  16  Added:  12
		Size:  13  Capacity:  16  Added:  13
		Size:  14  Capacity:  16  Added:  14
		Size:  15  Capacity:  16  Added:  15
		Size:  16  Capacity:  16  Added:  16
		Size:  17  Capacity:  32  Added:  17
		Size:  18  Capacity:  32  Added:  18
		Size:  19  Capacity:  32  Added:  19
		Size:  20  Capacity:  32  Added:  20

		** I observer a growth factor of 2x
	*/
	

	// Part C
	std::array<double, 5> arr = {1, 2, 3, 4, 5};
	std::vector<double> vec;


	for (int i= 1; i <= 20; ++i) {
		vec.push_back(static_cast<double>(i));
	}
	

	// get average for arr
	std::cout << "arr average: " << average(arr) << std::endl;

	// get average for vector
	std::cout << "vec average: " << average(vec) << std::endl;







}