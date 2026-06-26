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
