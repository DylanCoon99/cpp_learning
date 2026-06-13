// Exercise 2: Default Arguments
//
// Task: Write a function that formats a "progress bar" string.
//
// Function signature:
//   std::string progress_bar(int percent, int width = 20, char fill = '#', char empty = '.')
//
// It should return a string like: [####............]  25%
//
// Requirements:
//   - percent: 0-100 (clamp to this range if out of bounds)
//   - width: total number of fill+empty characters
//   - fill: character for completed portion
//   - empty: character for remaining portion
//   - Return a std::string (not just print it)
//
// In main(), demonstrate calling it with:
//   - Just percent:                progress_bar(50)
//   - Percent and width:           progress_bar(75, 30)
//   - All arguments:               progress_bar(30, 25, '=', '-')
//   - Print each returned string
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_defaults.cpp
// Example output:
//   [##########..........]  50%
//   [######################........]  75%
//   [=======-----------------]  30%

// YOUR CODE HERE
