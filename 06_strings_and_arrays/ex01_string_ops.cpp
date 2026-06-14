// Exercise 1: String Manipulation
//
// Task: Practice std::string operations.
//
// Part A — Basics:
//   - Create a string with your full name
//   - Print its length
//   - Print the first and last characters using .front() and .back()
//   - Print a substring of just your first name using .substr()
//   - Convert the entire string to uppercase (loop with std::toupper from <cctype>)
//   - Print the result
//
// Part B — Search and Replace:
//   - Start with the string: "the quick brown fox jumps over the lazy dog"
//   - Find the position of "fox" using .find()
//   - Replace "fox" with "cat" using .replace()
//   - Count how many times the letter 'e' appears
//   - Find the LAST occurrence of "the" using .rfind()
//   - Print all results
//
// Part C — Building strings:
//   - Read words from the user one at a time until they type "done"
//   - Concatenate them into a single string separated by spaces
//   - Print the final string and its word count
//   - Hint: use a while loop with std::cin >> word
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_string_ops.cpp

// YOUR CODE HERE
#include <string>
#include <iostream>


int main() {

	// Part A
	std::string name = "Dylan Coon";
	std::cout << "Length: " << name.size() << std::endl;
	std::cout << "First: " << name.front() << std::endl;
	std::cout << "Last: " << name.back() << std::endl;

	std::cout << "First Name: " << name.substr(0, 5) << std::endl;

	for (char& c: name) {
		c = std::toupper(c);
	}

	std::cout << "Uppercase: " << name << std::endl;


	// Part B
	std::string s = "the quick brown fox jumps over the lazy dog";

	int fox_location = s.find("fox");

	std::cout << "fox location: " << fox_location << std::endl;

	s.replace(fox_location, 3, "cat");

	std::cout << s << std::endl;

	int count = 0;

	for (char c: s) {
		if (c == 'e') {
			count++;
		}
	}

	std::cout << "'e' occurrences: " << count << std::endl;

	std::cout << "Last occurence of 'the': " << s.rfind("the") << std::endl;


	// Part C
	std::string input;
	std::string result = "";

	while (true) {
		std::cout << "Enter a word: ";
		std::cin >> input;
		if (input == "done") {
			break;
		}
		if (result == ""){
			result += input;
		} else {
			result += (" " + input);
		}
	}
	

	std::cout << "Result: " << result << std::endl;


}