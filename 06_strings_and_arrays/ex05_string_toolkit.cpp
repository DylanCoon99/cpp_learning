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
#include <iostream>
#include <ostream>
#include <string>


void print_info(const std::vector<std::string>& v) {

	for (std::string n: v) {
		std::cout << n << " ";
	}

	std::cout << std::endl;

}


std::string to_upper(const std::string& s) {
	std::string res;

	for (const char& c : s) {
		res += std::toupper(c);
	}

	return res;
}


std::string to_lower(const std::string& s) {
	std::string res;

	for (const char& c : s) {
		res += std::tolower(c);
	}

	return res;
}


std::string trim(const std::string& s) {

	std::string result = s;

	result.erase(0, s.find_first_not_of(" \t\n\r"));

	auto end = result.find_last_not_of(" \t\n\r");                                                                                                                                     
	if (end != std::string::npos) {                                                                                                                                                    
	  result.erase(end + 1);                                                                                                                                                         
	}


	return result;

}


std::string repeat(const std::string& s, int n) {

	std::string result = "";

	for (int i = 0; i < n; ++i) {
		result += s;
	}

	return result;
}


bool starts_with(const std::string& s, const std::string& prefix) {

	if (s.substr(0, prefix.size()) == prefix) {
		return true;
	}

	return false;

}


bool ends_with(const std::string& s, const std::string& suffix) {

	if (s.length() < suffix.length()) {
		return false;
	}

	if (s.substr(s.length() - suffix.length(), suffix.size()) == suffix) {
		return true;
	}

	return false;


}


std::vector<std::string> split(const std::string& s, char delimiter) {


	std::vector<std::string> result;

	std::string word = "";

	for (const char& c : s) {
		// build the word
		if (c == delimiter) {
			if (word != "") {
				result.push_back(word);
				word = "";
			} else {
				continue;
			}
		} else {
			word += c;
		}

	}
	if (word != "") {
		result.push_back(word);
	}

	return result;
}


std::string join(const std::vector<std::string>& parts, const std::string& sep) {

	std::string result = "";

	int size = static_cast<int>(parts.size());

	for (int i = 0; i < size; ++i) {
		if (i != size - 1) {
			result += (parts[i] + sep);
		} else {
			result += parts[i];
		}
	}

	return result;
}


std::string replace_all(const std::string& s,
                           const std::string& from, const std::string& to) {
	
	int idx;

	std::string result = s;

	while (result.find(from) != std::string::npos) {
		idx = result.find(from);
		result.replace(idx, from.length(), to);
	}

	return result;
}


int main() {

	std::string s = "dylan coon";
	std::cout << to_upper(s) << std::endl;
	std::cout << to_lower(to_upper(s)) << std::endl;

	std::string test_trim = "    testing trim";
	std::cout << trim(test_trim) << std::endl;


	std::string words = "Here is a sentence.";
	std::string lines = "Here\nis\na\ntest.";

	print_info(split(words, ' '));
	print_info(split(lines, '\n'));


	std::vector<std::string> parts = {"This", "is", "a", "test", "123", "456"};
	std::cout << join(parts, " ") << std::endl;
	std::cout << join(parts, "*") << std::endl;

	std::string test_replace = "abc def xyz abc";

	std::cout << replace_all(test_replace, "abc", "123") << std::endl;






}
