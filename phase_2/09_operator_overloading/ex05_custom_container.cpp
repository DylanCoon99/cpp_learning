// Exercise 5: Custom Container — SortedList
//
// Task: Build a sorted integer list that maintains elements in ascending
//       order. This exercises [], (), ++, <<, and comparison operators.
//
// Class definition:
//
//   class SortedList {
//   public:
//       SortedList() = default;
//       SortedList(std::initializer_list<int> init);  // SortedList s = {5,2,8,1};
//
//       // Element access
//       const int& operator[](int index) const;    // bounds-checked
//
//       // Functor: operator() as a "contains" check
//       bool operator()(int value) const;           // list(42) returns true if 42 is in list
//
//       // Insert (maintains sorted order)
//       SortedList& operator+=(int value);          // list += 5;
//       SortedList& operator+=(const SortedList& other);  // merge two lists
//
//       // Remove first occurrence
//       SortedList& operator-=(int value);          // list -= 5;
//
//       // Comparison (lexicographic)
//       bool operator==(const SortedList& rhs) const;
//       bool operator!=(const SortedList& rhs) const;
//       bool operator<(const SortedList& rhs) const;
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const SortedList& s);
//
//       // Info
//       int size() const;
//       bool empty() const;
//
//   private:
//       std::vector<int> data_;  // always kept sorted
//
//       void insert_sorted(int value);
//   };
//
// Requirements:
//   - initializer_list constructor should sort the input
//   - operator+= inserts in the correct sorted position (don't append+re-sort)
//     Use std::lower_bound to find the insertion point:
//       #include <algorithm>
//       auto it = std::lower_bound(data_.begin(), data_.end(), value);
//       data_.insert(it, value);
//   - operator() is a functor — using the object like a function call
//     to check membership. Use std::binary_search since data is sorted:
//       return std::binary_search(data_.begin(), data_.end(), value);
//   - Stream output format: [1, 3, 5, 7, 9]
//   - Merging two SortedLists should produce a sorted result
//
// In main():
//   - Create a list from initializer_list
//   - Insert elements with +=
//   - Print with <<
//   - Check membership with (): if (list(42)) { ... }
//   - Access elements with []
//   - Remove with -=
//   - Merge two lists
//   - Compare two lists
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_custom_container.cpp

// YOUR CODE HERE
