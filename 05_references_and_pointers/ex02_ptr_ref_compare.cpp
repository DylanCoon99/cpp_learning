// Exercise 2: Pointers vs. References Side-by-Side
//
// Task: Implement the same operations using both pointers and references
//       to see the syntactic and behavioral differences.
//
// Part A — Swap:
//   Write two versions of swap:
//     void swap_ptr(int* a, int* b)   — swap using pointers
//     void swap_ref(int& a, int& b)   — swap using references
//   Call both from main and print results.
//   Note the difference at the call site: swap_ptr(&x, &y) vs swap_ref(x, y)
//
// Part B — Find in array:
//   Write two versions:
//     int* find_ptr(int* arr, int size, int target)
//       — returns pointer to element, or nullptr if not found
//     int& find_ref(std::vector<int>& v, int target, bool& found)
//       — returns reference to element, uses bool to signal not-found
//       — if not found, return v[0] as a dummy (there's no "null reference")
//
//   This demonstrates WHY pointers are better when "not found" is possible:
//   pointers can be nullptr, references can't.
//
// Part C — Optional modification:
//   Write a function:
//     void maybe_double(int* p)
//   If p is not nullptr, double the value it points to. If null, do nothing.
//   This is a natural use of pointers — the null case is meaningful.
//   (You can't write this with a reference — it can't be null.)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_ptr_ref_compare.cpp

// YOUR CODE HERE
