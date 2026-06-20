// Exercise 2: Move Semantics — MyString
//
// Task: Add move constructor and move assignment to MyString.
//       This builds on exercise 1 (copy semantics must also work).
//
// Add to MyString:
//
//   // Move constructor — steal resources
//   MyString(MyString&& other) noexcept;
//
//   // Move assignment — steal resources, clean up old
//   MyString& operator=(MyString&& other) noexcept;
//
// Requirements:
//   - Move constructor: steal the pointer and size, set source to null/0
//   - Move assignment: free old data, steal, null out source
//   - Both must be noexcept
//   - After moving, the source must be in a valid state (safe to destroy,
//     but contents are unspecified)
//
// Also add a helper to observe moves:
//   - Add print statements (or a flag) in the copy/move constructors
//     so you can SEE which one gets called:
//       MyString(const MyString& other) {
//           std::cout << "COPY constructor\n";
//           // ...
//       }
//       MyString(MyString&& other) noexcept {
//           std::cout << "MOVE constructor\n";
//           // ...
//       }
//
// Write a function that returns a MyString:
//   MyString make_greeting(const char* name) {
//       MyString s("Hello, ");
//       s.append(name);
//       s.append("!");
//       return s;   // will this copy or move?
//   }
//
// In main():
//   - Create a MyString
//   - Copy it (should print "COPY constructor")
//   - Move it with std::move (should print "MOVE constructor")
//   - Verify the moved-from object is empty
//   - Call make_greeting — observe whether copy or move is used
//     (usually the compiler elides the copy entirely via NRVO —
//      Named Return Value Optimization — but it's good to see)
//   - Create a vector<MyString>, push_back several strings
//     When the vector reallocates, it will MOVE elements if your
//     move constructor is noexcept, or COPY if it isn't.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_move_semantics.cpp

// YOUR CODE HERE
