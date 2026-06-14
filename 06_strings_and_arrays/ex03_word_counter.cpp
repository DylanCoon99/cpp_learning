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
#include <iostream>
#include <string>
#include <sstream>


int main() {

	std::string line;
	std::cout << "Enter a line of text and press enter: ";
	std::getline(std::cin, line);

	int total_chars = line.size();
	int total_chars_minus_spaces = total_chars;
	int num_words = 0;
	int num_sentences = 0;
	int num_vowels = 0;
	std::vector<char> vowels = {'A', 'E', 'I', 'O', 'U'};


	// num sentences: count '.', '!', '?'
	for (const char& c: line) {
		if (c == '.' || c == '!' || c == '?') {
			num_sentences++;
		}
		else if (c ==  ' ') {
			total_chars_minus_spaces--;
		} else if (std::find(vowels.begin(), vowels.end(), std::toupper(c)) != vowels.end()) {
			// if c is in vowels
			num_vowels++;
		}
	}

	// reverse the string: use the two pointer method
	int end = line.length() - 1;
	std::string reverse_str;

	while (end >= 0) {
		std::string c(1, line[end]);
		reverse_str.append(c);
		end--;
	}


	// print each word on it's own line (also count the words)
	std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
        // process each word
        num_words++;
    }


	// print the results
	std::cout << "Total chars: " << total_chars << std::endl; 
	std::cout << "Non-space chars: " << total_chars_minus_spaces << std::endl; 
	std::cout << "Words: " << num_words << std::endl; 
	std::cout << "Sentences: " << num_sentences << std::endl; 
	std::cout << "Vowels: " << num_vowels << std::endl; 
	std::cout << "Reversed: " << reverse_str << std::endl; 
	std::cout << "Words: " << std::endl; 

	
	std::istringstream iss2(line);
    while (iss2 >> word) {
        // process each word
    	std::cout << word << std::endl; 
    }


	
}