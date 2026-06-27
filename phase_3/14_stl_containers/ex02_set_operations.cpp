// Exercise 2: Set Operations
//
// Task: Implement classic set operations using std::set.
//
// Part A — Basic set usage:
//   - Create a set<int> from: {5, 3, 8, 1, 9, 2, 7, 3, 5, 1}
//   - Print it (should be sorted, no duplicates)
//   - Test insert, erase, find, contains, count
//   - Print size
//
// Part B — Set operations:
//   Write these functions:
//
//   std::set<int> set_union(const std::set<int>& a, const std::set<int>& b);
//     — Return all elements in either a or b
//
//   std::set<int> set_intersection(const std::set<int>& a, const std::set<int>& b);
//     — Return only elements in BOTH a and b
//
//   std::set<int> set_difference(const std::set<int>& a, const std::set<int>& b);
//     — Return elements in a but NOT in b
//
//   bool is_subset(const std::set<int>& a, const std::set<int>& b);
//     — Return true if every element of a is also in b
//
//   Test with:
//     set<int> a = {1, 2, 3, 4, 5};
//     set<int> b = {3, 4, 5, 6, 7};
//     union: {1, 2, 3, 4, 5, 6, 7}
//     intersection: {3, 4, 5}
//     difference a-b: {1, 2}
//     difference b-a: {6, 7}
//
// Part C — unordered_set for fast lookup:
//   - Read words from user input
//   - Store in an unordered_set<string>
//   - Then ask the user for words to look up
//   - Report whether each word was in the input (O(1) average lookup)
//
// Part D — set of custom type:
//   Define a struct Point { int x, y; };
//   To put it in a std::set, you need operator<:
//     bool operator<(const Point& other) const {
//         if (x != other.x) return x < other.x;
//         return y < other.y;
//     }
//   - Create a set<Point>, insert several points
//   - Verify duplicates are rejected
//   - Iterate and print (will be sorted)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_set_operations.cpp

// YOUR CODE HERE
