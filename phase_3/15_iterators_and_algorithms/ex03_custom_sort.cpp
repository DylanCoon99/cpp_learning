// Exercise 3: Complex Sorting
//
// Task: Sort data by multiple criteria using custom comparators.
//
// Part A — Multi-field sort:
//   Define:
//     struct Employee {
//         std::string name;
//         std::string department;
//         double salary;
//         int years;
//     };
//
//   Create a vector of 8-10 employees across 3 departments.
//   Sort by:
//     1. Department ascending, then name ascending within each department
//     2. Salary descending (highest first)
//     3. Years descending, then salary descending for ties
//   Print after each sort.
//
// Part B — Stable sort:
//   - Sort employees by department using std::stable_sort
//   - Then stable_sort by salary within each department
//   - Demonstrate that stable_sort preserves the relative order of
//     equal elements (unlike std::sort which doesn't guarantee this)
//
// Part C — Partial sort:
//   - Use std::partial_sort to find only the top 3 highest-paid employees
//     without fully sorting the entire vector
//   - Use std::nth_element to find the median salary
//
// Part D — Custom sort for strings:
//   Create a vector<string> of words.
//   Sort by:
//     1. Length (shortest first)
//     2. Length descending, then alphabetically for same length
//     3. Case-insensitive alphabetical
//        (hint: compare tolower'd characters)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_custom_sort.cpp

// YOUR CODE HERE
#include <cctype>
#include <string>
#include <vector>
#include <iostream>


struct Employee {
	std::string name;
	std::string department;
	double salary;
	int years;
};


void print_employees(const std::vector<Employee>& employees) {
	for (const auto& employee : employees) {
		std::cout << "Name: " << employee.name << std::endl;
		std::cout << "Department: " << employee.department << std::endl;
		std::cout << "Salary: " << employee.salary << std::endl;
		std::cout << "Years: " << employee.years << std::endl;
		std::cout << std::endl;
	}
}


void print_words(const std::vector<std::string>& words) {
	for (const auto& word : words) {
		std::cout << word << std::endl;
		std::cout << std::endl;
	}

}


int main() {

	// Part A

	//     1. Department ascending, then name ascending within each department
	std::vector<Employee> employees = {
		{"Alice",   "Engineering", 95000,  5},
		{"Bob",     "Marketing",   72000,  3},
		{"Carol",   "Engineering", 110000, 8},
		{"Dan",     "Marketing",   68000,  2},
		{"Eve",     "Engineering", 95000,  6},
		{"Frank",   "Sales",       78000,  4},
		{"Grace",   "Sales",       82000,  7},
		{"Henry",   "Marketing",   75000,  5},
		{"Iris",    "Engineering", 105000, 3},
		{"Jack",    "Sales",       78000,  1},
	};

	std::sort(employees.begin(), employees.end(),                                                                                                                                      
      [](const Employee& a, const Employee& b) {                                                                                                                                     
          if (a.department != b.department) return a.department < b.department;                                                                                                      
          return a.name < b.name;                                                                                                                                                    
      });
	//print_employees(employees);
	
	//     2. Salary descending (highest first)
	std::sort(employees.begin(), employees.end(),
    	[](const Employee& a, const Employee& b) { return a.salary > b.salary; });
	
	//print_employees(employees);

	//     3. Years descending, then salary descending for ties
	std::sort(employees.begin(), employees.end(),                                                                                                                                      
      [](const Employee& a, const Employee& b) {                                                                                                                                     
          if (a.years != b.years) return a.years > b.years;                                                                                                      
          return a.salary > b.salary;                                                                                                                                                    
      }); 

	//print_employees(employees);


	// Part B

	//   - Sort employees by department using std::stable_sort
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) { return a.department < b.department;});
	//print_employees(employees);
	//   - Then stable_sort by salary within each department
	std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) { 
		if (a.department != b.department) { return a.department < b.department; }
		return a.salary < b.salary;});
	//print_employees(employees);
	//   - Demonstrate that stable_sort preserves the relative order of
	//     equal elements (unlike std::sort which doesn't guarantee this)

	// Part C — Partial sort:
	//   - Use std::partial_sort to find only the top 3 highest-paid employees
	//     without fully sorting the entire vector
	std::partial_sort(employees.begin(), employees.begin() + 3, employees.end(), 
		[](const Employee& a, const Employee& b) {return a.salary > b.salary;});
	//print_employees(employees);
	//   - Use std::nth_element to find the median salary
	std::nth_element(employees.begin(), employees.begin() + 5, employees.end(), 
		[](const Employee& a, const Employee& b) {return a.salary > b.salary;});
	print_employees(employees);

	// Part D — Custom sort for strings:
	std::vector<std::string> words = {
		"banana", "Apple", "fig", "cherry", "Date",
		"elderberry", "Grape", "kiwi", "Lemon", "mango",
		"ox", "pi", "a", "Blueberry", "cantaloupe"
	};
	//   Sort by:

	//     1. Length (shortest first)
	std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
		return a.length() < b.length();
	});
	//print_words(words);
	//     2. Length descending, then alphabetically for same length
	std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
		if (a.length() != b.length()) {return a.length() < b.length();};
		return a < b;
	});
	//print_words(words);
	//     3. Case-insensitive alphabetical
	std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
		std::string new_a, new_b;

		for (const char &c : a) {
	        new_a += std::tolower(static_cast<unsigned char>(c));
	    }

	    for (const char &c : b) {
	        new_b += std::tolower(static_cast<unsigned char>(c));
	    }


		return new_a < new_b;
	});
	print_words(words);
	//        (hint: compare tolower'd characters)

}