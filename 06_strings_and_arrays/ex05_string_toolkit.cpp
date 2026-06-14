// Exercise 5: String Toolkit
//
// Task: Build a collection of reusable string utility functions.
//       This is a mini-library exercise that pulls together strings,
//       vectors, loops, and functions.
//
// Implement these functions:
//
//   std::string to_upper(const std::string& s)
//     — Return a new string with all characters uppercase
//
//   std::string to_lower(const std::string& s)
//     — Return a new string with all characters lowercase
//
//   std::string trim(const std::string& s)
//     — Remove leading and trailing whitespace
//     — Hint: use s.find_first_not_of(" \t\n\r") and
//       s.find_last_not_of(" \t\n\r")
//
//   std::string repeat(const std::string& s, int n)
//     — Return the string repeated n times
//     — repeat("ab", 3) → "ababab"
//
//   bool starts_with(const std::string& s, const std::string& prefix)
//     — Return true if s starts with prefix
//     — Hint: use s.substr(0, prefix.size()) or s.compare(0, prefix.size(), prefix)
//     — Note: C++20 has s.starts_with() built in, but implement it yourself
//
//   bool ends_with(const std::string& s, const std::string& suffix)
//     — Return true if s ends with suffix
//
//   std::vector<std::string> split(const std::string& s, char delimiter)
//     — Split string by delimiter, return vector of parts
//     — split("a,b,c", ',') → {"a", "b", "c"}
//     — Hint: use std::istringstream and std::getline with delimiter:
//         std::istringstream iss(s);
//         std::string token;
//         while (std::getline(iss, token, delimiter)) { ... }
//
//   std::string join(const std::vector<std::string>& parts, const std::string& sep)
//     — Opposite of split: join({"a","b","c"}, ", ") → "a, b, c"
//     — Don't add separator after the last element
//
//   std::string replace_all(const std::string& s,
//                           const std::string& from, const std::string& to)
//     — Replace all occurrences of 'from' with 'to'
//     — "hello world hello" replace "hello" with "hi" → "hi world hi"
//
// In main():
//   - Test each function and print results
//   - Demonstrate split + join roundtrip: split a CSV line, then join it back
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_string_toolkit.cpp

// YOUR CODE HERE
