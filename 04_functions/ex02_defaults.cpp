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
#include <iostream>
#include <string>


std::string progress_bar(int percent, int width = 20, char fill = '#', char empty = '.') {

	std::string progress = "[";


	percent = percent > 100 ? 100 : (percent < 0 ? 0 : percent);

	// determine how many fill chars and how many empty chars

	int num_filled = static_cast<int>(static_cast<float>(percent) / 100 * width); // this line needs fixed


	for (int i = 0; i < width; ++i) {
		if (i <= num_filled) {
			progress += fill;
		} else {
			progress += empty;
		}
	}

	progress += "] ";
	progress += std::to_string(percent);
	progress += "%";

	return progress;
}


int main() {


	// call the progress bar function
	std::cout << progress_bar(50) << std::endl;
	std::cout << progress_bar(75, 30) << std::endl;
	std::cout << progress_bar(30, 25, '=', '-') << std::endl;


}