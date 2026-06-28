// Exercise 5: Custom Iterator
//
// Task: Build a container class with its own iterator so it works with
//       range-based for loops and STL algorithms.
//
// Build a Range class that generates a sequence of numbers lazily
// (like Python's range()):
//
//   class Range {
//   public:
//       Range(int start, int end, int step = 1);
//
//       class Iterator {
//       public:
//           // These type aliases are required for STL compatibility:
//           using iterator_category = std::forward_iterator_tag;
//           using value_type = int;
//           using difference_type = std::ptrdiff_t;
//           using pointer = const int*;
//           using reference = const int&;
//
//           Iterator(int value, int step);
//
//           int operator*() const;          // dereference
//           Iterator& operator++();          // pre-increment
//           Iterator operator++(int);        // post-increment
//           bool operator==(const Iterator& other) const;
//           bool operator!=(const Iterator& other) const;
//
//       private:
//           int current_;
//           int step_;
//       };
//
//       Iterator begin() const;
//       Iterator end() const;
//
//   private:
//       int start_, end_, step_;
//   };
//
// Requirements:
//   - begin() returns Iterator(start_, step_)
//   - end() returns Iterator(end_, step_)
//   - ++ advances current_ by step_
//   - The end iterator should work correctly for steps > 1:
//     Range(0, 10, 3) should produce: 0, 3, 6, 9
//     The end condition should be current_ >= end_ (for positive step)
//
// Usage:
//
//   // Range-based for loop (like Python!)
//   for (int x : Range(0, 10)) {
//       std::cout << x << " ";   // 0 1 2 3 4 5 6 7 8 9
//   }
//
//   for (int x : Range(0, 20, 3)) {
//       std::cout << x << " ";   // 0 3 6 9 12 15 18
//   }
//
//   for (int x : Range(10, 0, -1)) {
//       std::cout << x << " ";   // 10 9 8 7 6 5 4 3 2 1
//   }
//
//   // Works with STL algorithms!
//   Range r(1, 11);
//   int sum = std::accumulate(r.begin(), r.end(), 0);  // 55
//
//   auto it = std::find(r.begin(), r.end(), 7);
//   if (it != r.end()) std::cout << "found: " << *it;
//
//   int evens = std::count_if(r.begin(), r.end(),
//       [](int x) { return x % 2 == 0; });   // 5
//
//   // Copy to a vector
//   std::vector<int> v(r.begin(), r.end());   // {1, 2, ..., 10}
//
// Bonus:
//   Make it work with negative steps: Range(10, 0, -1) counts down.
//   The end condition changes: current_ > end_ for negative step.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_custom_iterator.cpp

// YOUR CODE HERE
