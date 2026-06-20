// Exercise 5: DynamicArray — A Complete Resizable Array
//
// Task: Build a production-quality dynamic array (simplified std::vector)
//       with full Rule of Five, operator overloading, and proper memory
//       management. This pulls together everything from Phase 2.
//
// Class definition:
//
//   class DynamicArray {
//   public:
//       // Constructors
//       DynamicArray();                              // default: empty
//       explicit DynamicArray(int capacity);          // pre-allocated
//       DynamicArray(std::initializer_list<int> init); // DynamicArray a = {1,2,3};
//
//       // Rule of Five
//       ~DynamicArray();
//       DynamicArray(const DynamicArray& other);
//       DynamicArray& operator=(const DynamicArray& other);
//       DynamicArray(DynamicArray&& other) noexcept;
//       DynamicArray& operator=(DynamicArray&& other) noexcept;
//
//       // Element access
//       int& operator[](int index);
//       const int& operator[](int index) const;
//       int& at(int index);                          // bounds-checked
//       const int& at(int index) const;
//       int& front();
//       int& back();
//
//       // Capacity
//       int size() const;
//       int capacity() const;
//       bool empty() const;
//       void reserve(int new_cap);                   // grow capacity
//       void shrink_to_fit();                        // reduce capacity to size
//
//       // Modifiers
//       void push_back(int value);
//       int pop_back();
//       void insert(int index, int value);
//       void erase(int index);
//       void clear();
//       void resize(int new_size, int fill = 0);
//
//       // Comparison
//       bool operator==(const DynamicArray& other) const;
//       bool operator!=(const DynamicArray& other) const;
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
//
//       // Swap
//       void swap(DynamicArray& other) noexcept;
//
//   private:
//       int* data_;
//       int size_;
//       int capacity_;
//
//       void grow();   // double capacity
//   };
//
// Requirements:
//   - Use copy-and-swap for copy assignment
//   - Move operations must be noexcept
//   - reserve() only grows, never shrinks
//   - push_back calls grow() when full
//   - insert/erase shift elements as needed
//   - Stream output: [1, 2, 3, 4, 5]
//   - at() throws std::out_of_range
//   - All Rule of Five functions must be correct (no double-free, no leaks)
//
// In main():
//   - Create arrays with each constructor
//   - Test push_back, pop_back, insert, erase
//   - Test copy construction and assignment
//   - Test move construction and assignment
//   - Put DynamicArrays in a std::vector<DynamicArray> — this stress-tests
//     your copy/move operations
//   - Test initializer_list: DynamicArray a = {10, 20, 30};
//   - Print everything with <<
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_dynamic_array.cpp

// YOUR CODE HERE
