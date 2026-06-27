// Exercise 1: Word Frequency Counter
//
// Task: Build a word frequency counter that demonstrates map and
//       unordered_map usage.
//
// Part A — Word frequency with std::map:
//   - Read a line of text from the user (std::getline)
//   - Split into words (use std::istringstream)
//   - Convert each word to lowercase
//   - Count occurrences using std::map<std::string, int>
//   - Print all words and their counts (will be alphabetically sorted)
//   - Print the most frequent word
//   - Print total unique words
//
// Part B — Same thing with std::unordered_map:
//   - Do the same counting with unordered_map
//   - Print results — note the different iteration order
//   - Compare: same data, different ordering
//
// Part C — Character frequency:
//   - Count the frequency of each character in the input string
//   - Use std::map<char, int>
//   - Print in sorted order
//   - Skip spaces
//
// Part D — map of vectors:
//   Build a std::map<std::string, std::vector<int>> to store test scores
//   by student name:
//     scores["Alice"].push_back(95);
//     scores["Alice"].push_back(87);
//     scores["Bob"].push_back(72);
//
//   - Add scores for 3-4 students (multiple scores each)
//   - Print each student and their average score
//   - Find the student with the highest average
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_map_basics.cpp

// YOUR CODE HERE
