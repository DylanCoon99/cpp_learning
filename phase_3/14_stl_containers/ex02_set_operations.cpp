// Exercise 2: Set Operations
//
// Task: Implement classic set operations using std::set.
//
// Part A — Basic set usage:
//   - Create a set<int> from: {5, 3, 8, 1, 9, 2, 7, 3, 5, 1}
//   - Print it (should be sorted, no duplicates)
//   - Test insert, erase, find, contains, count
//   - Print size
//
// Part B — Set operations:
//   Write these functions:
//
//   std::set<int> set_union(const std::set<int>& a, const std::set<int>& b);
//     — Return all elements in either a or b
//
//   std::set<int> set_intersection(const std::set<int>& a, const std::set<int>& b);
//     — Return only elements in BOTH a and b
//
//   std::set<int> set_difference(const std::set<int>& a, const std::set<int>& b);
//     — Return elements in a but NOT in b
//
//   bool is_subset(const std::set<int>& a, const std::set<int>& b);
//     — Return true if every element of a is also in b
//
//   Test with:
//     set<int> a = {1, 2, 3, 4, 5};
//     set<int> b = {3, 4, 5, 6, 7};
//     union: {1, 2, 3, 4, 5, 6, 7}
//     intersection: {3, 4, 5}
//     difference a-b: {1, 2}
//     difference b-a: {6, 7}
//
// Part C — unordered_set for fast lookup:
//   - Read words from user input
//   - Store in an unordered_set<string>
//   - Then ask the user for words to look up
//   - Report whether each word was in the input (O(1) average lookup)
//
// Part D — set of custom type:
//   Define a struct Point { int x, y; };
//   To put it in a std::set, you need operator<:
//     bool operator<(const Point& other) const {
//         if (x != other.x) return x < other.x;
//         return y < other.y;
//     }
//   - Create a set<Point>, insert several points
//   - Verify duplicates are rejected
//   - Iterate and print (will be sorted)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_set_operations.cpp

// YOUR CODE HERE
#include <set>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>


std::set<int> set_union(const std::set<int>& a, const std::set<int>& b) {
	//     — Return all elements in either a or b
	std::set<int> result;

	for (auto &elem : a) {
		result.insert(elem);
	}
	for (auto &elem : b) {
		result.insert(elem);
	}
	return result;
}


std::set<int> set_intersection(const std::set<int>& a, const std::set<int>& b) {
	//     — Return only elements in BOTH a and b
	std::set<int> result;

	for (auto &elem : a) {
		if (b.contains(elem)) {
			result.insert(elem);
		}
	}
	return result;
}


std::set<int> set_difference(const std::set<int>& a, const std::set<int>& b) {
	//     — Return elements in a but NOT in b
	std::set<int> result;
	
	for (auto &elem : a) {
		if (!b.contains(elem)) {
			result.insert(elem);
		}
	}
	return result;
}

bool is_subset(const std::set<int>& a, const std::set<int>& b) {
	//     — Return true if every element of a is also in b
	
	for (auto &elem : a) {
		if (!b.contains(elem)) {
			return false;
		}
	}
	return true;
}


void print_set(const std::set<int>& set) {
	for (int x : set) {
    	std::cout << x << " ";  // 1 3 4 5 6
	}
	std::cout << std::endl;
}


// Part D
struct Point {
	int x, y;
	bool operator<(const Point& other) const;
};


bool Point::operator<(const Point& other) const {
	if (x != other.x) return x < other.x;
	return y < other.y;
}

int main() {

	// Part A — Basic set usage:
	//   - Create a set<int> from: {5, 3, 8, 1, 9, 2, 7, 3, 5, 1}
	std::set<int> my_set = {5, 3, 8, 1, 9, 2, 7, 3, 5, 1};
	//   - Print it (should be sorted, no duplicates)
	print_set(my_set);
	
	//   - Test insert, erase, find, contains, count
	my_set.insert(10);
	my_set.erase(1);
	std::cout << "my_set.contains(1): " << (my_set.contains(1) ? "true" : "false") << std::endl;
	std::cout << "my_set.contains(10): " << (my_set.contains(10) ? "true" : "false") << std::endl;
	//   - Print size
	std::cout << "my_set.size(): " << my_set.size() << std::endl;

	// Part B — Set operations:
	std::set<int> a = {1, 2, 3, 4, 5};
	std::set<int> b = {3, 4, 5, 6, 7};
	print_set(std::move(set_union(a, b)));
	print_set(std::move(set_intersection(a, b)));
	print_set(std::move(set_difference(a, b)));
	print_set(std::move(set_difference(b, a)));

	// Part C — unordered_set for fast lookup:
	//   - Read words from user input
	std::unordered_set<std::string> my_words;
	// prompt user for input
	std::string input;
	std::cin >> input;
	std::getline(std::cin, input);
	std::istringstream iss(input);
	std::string word;
	std::string word_input;

	while (iss >> word) {
		//   - Store in an unordered_set<string>
		my_words.insert(word);
	}

	//   - Then ask the user for words to look up
	std::cout << "Provide a word to look up: ";
	std::cin >> word_input;
	//   - Report whether each word was in the input (O(1) average lookup)
	std::cout << "Word is " << (my_words.contains(word_input) ? "" : "not ") << "in the input." << std::endl;


	// Part D
	std::set<Point> points;
	points.insert({1, 2});
	points.insert({3, 4});
	points.insert({1, 5});
	points.insert({1, 2});   // duplicate — should be rejected
	points.insert({0, 0});
	points.insert({3, 4});   // duplicate — should be rejected

	std::cout << "points.size(): " << points.size() << " (expected 4)" << std::endl;

	std::cout << "Points (sorted):" << std::endl;
	for (const auto& p : points) {
		std::cout << "  (" << p.x << ", " << p.y << ")" << std::endl;
	}

}