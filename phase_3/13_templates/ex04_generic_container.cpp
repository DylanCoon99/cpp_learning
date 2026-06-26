// Exercise 4: Generic DynamicArray<T>
//
// Task: Take your DynamicArray from step 11 ex05 and make it generic
//       using templates. It should work with any type, not just int.
//
// template <typename T>
// class DynamicArray {
// public:
//     DynamicArray();
//     explicit DynamicArray(int capacity);
//     DynamicArray(std::initializer_list<T> init);
//
//     // Rule of Five
//     ~DynamicArray();
//     DynamicArray(const DynamicArray& other);
//     DynamicArray& operator=(DynamicArray other);   // copy-and-swap
//     DynamicArray(DynamicArray&& other) noexcept;
//     DynamicArray& operator=(DynamicArray&& other) noexcept;
//
//     // Element access
//     T& operator[](int index);
//     const T& operator[](int index) const;
//
//     // Modifiers
//     void push_back(const T& value);
//     void push_back(T&& value);         // move version!
//     T pop_back();
//     void clear();
//
//     // Capacity
//     int size() const;
//     int capacity() const;
//     bool empty() const;
//
//     // Swap
//     void swap(DynamicArray& other) noexcept;
//
//     // Stream
//     friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
//         // Note: friend functions in templates must be defined inline
//         os << "[";
//         for (int i = 0; i < arr.size_; ++i) {
//             if (i > 0) os << ", ";
//             os << arr.data_[i];
//         }
//         os << "]";
//         return os;
//     }
//
// private:
//     T* data_;
//     int size_;
//     int capacity_;
//     void grow();
// };
//
// Key changes from the int version:
//   - Replace int* data_ with T* data_
//   - Replace new int[] with new T[]
//   - Add a T&& (rvalue reference) overload of push_back for move semantics
//   - The << operator must be defined inline inside the class (template friend
//     functions are tricky if defined outside)
//
// The move-aware push_back:
//   void push_back(T&& value) {
//       if (size_ == capacity_) grow();
//       data_[size_] = std::move(value);  // move instead of copy
//       ++size_;
//   }
//   This matters when T is something expensive to copy (like std::string).
//
// In main():
//   DynamicArray<int> ints = {1, 2, 3};
//   ints.push_back(4);
//   std::cout << ints << "\n";
//
//   DynamicArray<std::string> strs;
//   strs.push_back("hello");
//   strs.push_back("world");
//   std::cout << strs << "\n";
//
//   DynamicArray<double> dbls = {1.1, 2.2, 3.3};
//   std::cout << dbls << "\n";
//
//   // Copy and move
//   auto copy = ints;
//   auto moved = std::move(strs);
//   std::cout << "moved: " << moved << "\n";
//   std::cout << "strs empty: " << strs.empty() << "\n";
//
//   // Nested
//   DynamicArray<DynamicArray<int>> nested;
//   nested.push_back(DynamicArray<int>{1, 2});
//   nested.push_back(DynamicArray<int>{3, 4});
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_generic_container.cpp

// YOUR CODE HERE
