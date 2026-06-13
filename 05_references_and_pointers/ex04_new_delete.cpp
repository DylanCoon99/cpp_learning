// Exercise 4: new and delete
//
// Task: Practice manual heap allocation. (In real code, use smart pointers —
//       this exercise exists so you understand what's happening underneath.)
//
// Part A — Single objects:
//   - Allocate an int on the heap with new, initialize to 42
//   - Print its value and address
//   - Delete it
//   - Set the pointer to nullptr after delete (good practice)
//
// Part B — Arrays:
//   - Ask the user for a size n
//   - Allocate an array of n ints with new[]
//   - Fill it with squares: arr[i] = (i+1)*(i+1)
//   - Print all elements
//   - Delete with delete[] (NOT delete — that's undefined behavior)
//
// Part C — A dynamically allocated struct:
//   Define:
//     struct Point {
//         double x;
//         double y;
//     };
//
//   - Allocate a Point with new
//   - Set its x and y (use -> since it's a pointer)
//   - Write a function: double distance(const Point* a, const Point* b)
//     that computes Euclidean distance (use <cmath> for std::sqrt)
//   - Create two Points, compute distance, print it
//   - Delete both
//
// Part D — Memory leak detector (mental exercise):
//   Look at this code and identify the leak:
//
//     void leaky() {
//         int* p = new int(10);
//         if (some_condition) return;   // LEAK: p never deleted
//         delete p;
//     }
//
//   Write a comment explaining why this leaks and how you'd fix it.
//   (The real fix is smart pointers — for now, just restructure the code.)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_new_delete.cpp

// YOUR CODE HERE
