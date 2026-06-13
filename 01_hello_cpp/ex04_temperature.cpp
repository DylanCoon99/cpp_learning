// Exercise 4: Temperature Converter
//
// Task: Read a temperature in Fahrenheit, convert it to Celsius,
//       and print the result with exactly 2 decimal places.
//
// Formula: C = (F - 32) * 5.0 / 9.0
//
// Requirements:
//   - Use double for the temperature values
//   - Format output to 2 decimal places
//   - Hint: #include <iomanip> gives you std::fixed and std::setprecision()
//
//   Example usage:
//     std::cout << std::fixed << std::setprecision(2) << some_double;
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_temperature.cpp
// Example session:
//   Enter temperature in Fahrenheit: 212
//   212.00°F = 100.00°C

// YOUR CODE HERE
#include <iostream>


int main() {

	double fahrenheit;
	double celsius;

	std::cout << "Enter temperature in Fahrenheit: ";
	std::cin >> fahrenheit;


	celsius = (fahrenheit - 32) * 5.0 / 9;

	std::cout << fahrenheit << "°F = " << celsius << "°C";



	return 0;
}