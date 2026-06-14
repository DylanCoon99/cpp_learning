// Exercise 3: Word and Character Counter
//
// Task: Build a text analysis tool.
//
// Requirements:
//   - Read a full line of text from the user using std::getline(std::cin, line)
//     (not std::cin >> ... which stops at whitespace)
//   - Count and print:
//       - Total characters (including spaces)
//       - Total characters (excluding spaces)
//       - Number of words (split by spaces)
//       - Number of sentences (count '.', '!', '?')
//       - Number of vowels (a, e, i, o, u — case-insensitive)
//   - Print the text reversed (build a reversed string)
//   - Print each word on its own line (you'll need to split by spaces)
//
// Hint for splitting by spaces:
//   You can use std::istringstream from <sstream>:
//     #include <sstream>
//     std::istringstream iss(line);
//     std::string word;
//     while (iss >> word) {
//         // process each word
//     }
//   This is the idiomatic C++ way to split a string by whitespace.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_word_counter.cpp
// Example:
//   Enter text: Hello, World! This is C++.
//   Total chars: 26
//   Non-space chars: 22
//   Words: 5
//   Sentences: 2
//   Vowels: 6
//   Reversed: .++C si sihT !dlroW ,olleH
//   Words:
//     Hello,
//     World!
//     This
//     is
//     C++.

// YOUR CODE HERE
