// Exercise 2: MyString — A Simplified String Class with RAII
//
// Task: Build your own string class that manages a dynamic char array.
//       This teaches you exactly what std::string does under the hood.
//
// Class definition:
//
//   class MyString {
//   public:
//       MyString();                              // default: empty string
//       MyString(const char* str);               // from C-string
//       ~MyString();                             // free the memory
//
//       // Getters
//       int length() const;
//       const char* c_str() const;               // return raw pointer
//       bool empty() const;
//       char at(int index) const;                // bounds-checked access
//
//       // Modifiers
//       void append(const char* str);
//       void clear();
//
//       // Utility
//       void print() const;
//       int find(char c) const;                  // return index or -1
//
//   private:
//       char* data_;        // dynamically allocated char array
//       int length_;        // length (not counting null terminator)
//
//       // Helper
//       void copy_from(const char* str);         // allocate and copy
//   };
//
// Requirements:
//   - Constructor allocates memory with new[]
//   - Destructor frees with delete[]
//   - Store strings as null-terminated char arrays (like C strings)
//   - append() must allocate a new, larger buffer, copy old + new, delete old
//   - Use std::strlen and std::strcpy from <cstring>
//   - Do NOT use std::string anywhere — the point is to manage memory yourself
//
// In main():
//   - Create a MyString from a C-string literal
//   - Print it and its length
//   - Append to it, print again
//   - Test at() with valid and invalid indices
//   - Test find()
//   - Clear it, verify empty
//   - Create a default (empty) MyString, verify it works
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_string_class.cpp

// YOUR CODE HERE
