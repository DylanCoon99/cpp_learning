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
