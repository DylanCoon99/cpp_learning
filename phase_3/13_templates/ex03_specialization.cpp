// Exercise 3: Template Specialization
//
// Task: Practice full and partial template specialization.
//
// Part A — Full specialization of a function template:
//
//   Write a generic to_string:
//     template <typename T>
//     std::string to_string(const T& value);
//       — Default: use std::to_string(value) for numeric types
//
//   Specialize for:
//     template <> std::string to_string<bool>(const bool& value);
//       — return "true" or "false"
//
//     template <> std::string to_string<char>(const char& value);
//       — return a single-character string
//
//     template <> std::string to_string<std::string>(const std::string& value);
//       — return the string itself (std::to_string doesn't work on strings)
//
//   Test: to_string(42), to_string(true), to_string('A'), to_string(std::string("hi"))
//
// Part B — Full specialization of a class template:
//
//   template <typename T>
//   class Formatter {
//   public:
//       static std::string format(const T& value) {
//           return "[" + std::to_string(value) + "]";
//       }
//   };
//
//   Specialize for std::string:
//     template <>
//     class Formatter<std::string> {
//     public:
//         static std::string format(const std::string& value) {
//             return "\"" + value + "\"";
//         }
//     };
//
//   Specialize for bool:
//     Returns "[YES]" or "[NO]"
//
//   Test all: Formatter<int>::format(42), Formatter<std::string>::format("hello"),
//             Formatter<bool>::format(true)
//
// Part C — Partial specialization:
//
//   template <typename T>
//   class Container {
//   public:
//       void store(const T& value);
//       void print() const;
//   private:
//       T value_;
//   };
//
//   Partial specialization for pointers:
//   template <typename T>
//   class Container<T*> {
//       — stores a pointer
//       — print() dereferences and prints the pointed-to value
//       — add is_null() method
//   };
//
//   Partial specialization for vectors:
//   template <typename T>
//   class Container<std::vector<T>> {
//       — stores a vector
//       — print() prints all elements
//       — add size() method
//   };
//
//   Test: Container<int>, Container<int*>, Container<std::vector<int>>
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_specialization.cpp

// YOUR CODE HERE
