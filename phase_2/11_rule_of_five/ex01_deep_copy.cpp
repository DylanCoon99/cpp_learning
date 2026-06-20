// Exercise 1: Deep Copy — Fix MyString
//
// Task: Take your MyString class from step 08 ex02 and add proper
//       copy semantics. Without them, copying a MyString causes a
//       double-free crash.
//
// Add to MyString:
//
//   // Copy constructor — deep copy
//   MyString(const MyString& other);
//
//   // Copy assignment — deep copy with cleanup
//   MyString& operator=(const MyString& other);
//
// Requirements:
//   - Copy constructor: allocate new memory, copy the characters
//   - Copy assignment: free old memory, allocate new, copy
//   - Handle self-assignment in operator= (what if a = a?)
//   - After copying, both objects must be fully independent
//     (modifying one doesn't affect the other)
//
// Also add:
//   - operator<< for easy printing
//   - operator== to compare two MyStrings
//
// In main():
//   - Create a MyString
//   - Copy construct another: MyString b = a;
//   - Modify a, verify b is unchanged (proves deep copy)
//   - Copy assign: b = a;
//   - Self-assign: a = a; (should not crash)
//   - Put MyStrings in a vector — this triggers copy constructor
//     when the vector reallocates. Without proper copy semantics,
//     this would crash.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_deep_copy.cpp

// YOUR CODE HERE
