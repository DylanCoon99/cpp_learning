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
#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>


int main() {
	/*
	{
		// Part A
		std::map<std::string, int> word_frequency;

		// prompt user for input
		std::string input;
		std::cin >> input;
		std::getline(std::cin, input);
		std::istringstream iss(input);
		std::string word;

		while (iss >> word) {
			// add each word to the map
			if (word_frequency.count(word)) {
				word_frequency[word] += 1;
			} else {
				word_frequency[word] = 1;
			}
		}

		int highest_freq = 0;
		std::string most_freq_word;

		// print the map (word, frequency)
		for (const auto &[word, frequency] : word_frequency) { 
			if (frequency > highest_freq) {
				highest_freq = frequency;
				most_freq_word = word;
			}
			std::cout << word << ": " << frequency << std::endl;
		}

		std::cout << std::endl;

		std::cout << "Most frequent word: " << most_freq_word << "  freq: " << highest_freq << std::endl;

		std::cout << "There are " << word_frequency.size() << " unique words." << std::endl;
	}
	*/
	/*
	{
		// Part B
		std::unordered_map<std::string, int> word_frequency;

		// prompt user for input
		std::string input;
		std::cin >> input;
		std::getline(std::cin, input);
		std::istringstream iss(input);
		std::string word;

		while (iss >> word) {
			// add each word to the map
			if (word_frequency.count(word)) {
				word_frequency[word] += 1;
			} else {
				word_frequency[word] = 1;
			}
		}

		int highest_freq = 0;
		std::string most_freq_word;

		// print the map (word, frequency)
		for (const auto &[word, frequency] : word_frequency) { 
			if (frequency > highest_freq) {
				highest_freq = frequency;
				most_freq_word = word;
			}
			std::cout << word << ": " << frequency << std::endl;
		}

		std::cout << std::endl;

		std::cout << "Most frequent word: " << most_freq_word << "  freq: " << highest_freq << std::endl;

		std::cout << "There are " << word_frequency.size() << " unique words." << std::endl;
	}
	*/

	/*
	{
		// Part C
		std::map<char, int> char_frequency;

		// prompt user for input
		std::string input;
		std::cin >> input;
		std::getline(std::cin, input);
		char c;

		for (int i = 0; i < static_cast<int>(input.length()); ++i) {
			// add each word to the map
			c = input.at(i);
			if (c != ' ') {
				if (char_frequency.count(c)) {
					char_frequency[c] += 1;
				} else {
					char_frequency[c] = 1;
				}
			}
		}

		int highest_freq = 0;
		char most_freq_char;

		// print the map (word, frequency)
		for (const auto &[c, frequency] : char_frequency) { 
			if (frequency > highest_freq) {
				highest_freq = frequency;
				most_freq_char= c;
			}
			std::cout << c << ": " << frequency << std::endl;
		}

		std::cout << std::endl;

		std::cout << "Most frequent word: " << most_freq_char << "  freq: " << highest_freq << std::endl;

		std::cout << "There are " << char_frequency.size() << " unique chars." << std::endl;
	}
	*/

	{
		// Part D
		std::map<std::string, std::vector<int>> scores;
		scores["Alice"].push_back(95);
		scores["Alice"].push_back(87);
		scores["Bob"].push_back(72);
		scores["John"].push_back(47);
		scores["John"].push_back(67);

		int highest_avg = 0;
		std::string best_student;

		for (auto &[student, test_scores] : scores) {
			double avg = 0.0;
			for (auto &score : test_scores) {
				avg += score;
			}
			avg /= test_scores.size();
			if (avg > highest_avg) {
				highest_avg = avg;
				best_student = student;
			}
			// print student name and average score
			std::cout << "Student: " << student << "   Avg: " << avg << std::endl;
		}

		std::cout << "The best student is: " << best_student << " and their average was: " << highest_avg << std::endl;

	}

}