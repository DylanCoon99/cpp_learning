// Exercise 1: Iterator Fundamentals
//
// Task: Practice different ways to traverse and manipulate containers
//       using iterators.
//
// Part A — Basic traversal:
//   Create a vector<int> with values 10-100 (step 10).
//   Traverse and print using:
//     1. Index-based for loop
//     2. Iterator-based for loop (auto it = v.begin(); it != v.end(); ++it)
//     3. Range-based for loop
//     4. Reverse iterators (rbegin/rend)
//     5. const iterators (cbegin/cend)
//
// Part B — Iterator arithmetic:
//   - Use std::advance to move an iterator to the 5th element
//   - Use std::next and std::prev to get neighboring elements
//   - Use std::distance to compute how far apart two iterators are
//   - Use iterator subtraction (it2 - it1) for the same thing (vector only)
//
// Part C — Iterating different containers:
//   Create and iterate each, printing all elements:
//     - std::list<std::string> (bidirectional iterators)
//     - std::set<int> (bidirectional iterators)
//     - std::map<std::string, int> (bidirectional, structured bindings)
//   Try: can you use it + 3 on a list iterator? Why not?
//   (list iterators are bidirectional, not random access)
//
// Part D — Modifying through iterators:
//   - Create a vector<int> of 10 elements
//   - Use an iterator loop to double every element
//   - Use an iterator to insert an element in the middle
//     (v.insert(it, value) — returns iterator to inserted element)
//   - Use an iterator to erase every other element
//     (careful: erase invalidates iterators! Use: it = v.erase(it))
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_iterator_basics.cpp

// YOUR CODE HERE
