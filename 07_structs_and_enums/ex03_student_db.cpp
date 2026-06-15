// Exercise 3: Student Database
//
// Task: Build a mini student database using a vector of structs.
//
// Define:
//   enum class Year { Freshman, Sophomore, Junior, Senior };
//
//   struct Student {
//       std::string name;
//       int id;
//       Year year;
//       double gpa;
//   };
//
// Implement these functions:
//
//   void print_student(const Student& s)
//     — Print: "ID: 1234 | Dylan (Junior) | GPA: 3.75"
//
//   void print_all(const std::vector<Student>& students)
//     — Print all students
//
//   double average_gpa(const std::vector<Student>& students)
//     — Return average GPA
//
//   Student* find_by_id(std::vector<Student>& students, int id)
//     — Return pointer to student with given ID, or nullptr if not found
//     — This is a good use of pointer return (nullable result)
//
//   std::vector<Student> filter_by_year(const std::vector<Student>& students, Year y)
//     — Return a new vector of students in the given year
//
//   void sort_by_gpa(std::vector<Student>& students)
//     — Sort students by GPA descending (highest first)
//     — Use std::sort with a comparison function:
//         std::sort(students.begin(), students.end(),
//                   [](const Student& a, const Student& b) {
//                       return a.gpa > b.gpa;
//                   });
//     — The [](...)  {...} is a LAMBDA — a preview of step 16.
//       For now just use it as shown. It's an inline comparison function.
//
// In main():
//   - Create a vector of at least 6 students with varied years and GPAs
//   - Print all
//   - Print average GPA
//   - Find a student by ID, modify their GPA through the pointer
//   - Filter Juniors, print them
//   - Sort by GPA, print all
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_student_db.cpp

// YOUR CODE HERE
#include <iostream>
#include <string>
#include <iomanip>


enum class Year { Freshman, Sophomore, Junior, Senior };


std::string year_to_string(Year y) {
	switch (y) {
	case Year::Freshman:
		return "Freshman";
	case Year::Sophomore:
		return "Sophomore";
	case Year::Junior:
		return "Junior";
	case Year::Senior:
		return "Senior";
	}
}

struct Student {
	std::string name;
	int id;
	Year year;
	double gpa;
};


void print_student(const Student& s) {
	std::cout << std::fixed << std::setprecision(2) << "ID: " << s.id << " | " << s.name << " (" << year_to_string(s.year) << ") | GPA: " << s.gpa << std::endl;
}


void print_all(const std::vector<Student>& students) {
	for (const auto& s : students) {
		print_student(s);
	}
	std::cout << std::endl;
}


double average_gpa(const std::vector<Student>& students) {

	double avg = 0.0;

	for (const auto& s : students) {
		avg += s.gpa;
	}

	return avg / students.size();
}


Student* find_by_id(std::vector<Student>& students, int id) {

	for (auto& s : students) {
		if (s.id == id) {
			return &s;
		}
	}
	return nullptr;
}


std::vector<Student> filter_by_year(const std::vector<Student>& students, Year y) {
	std::vector<Student> filtered;

	for (const auto& s : students) {
		if (s.year == y) {
			filtered.push_back(s);
		}
	}

	return filtered;
}


void sort_by_gpa(std::vector<Student>& students) {
	std::sort(students.begin(), students.end(), 
		[](const Student& a, const Student& b) {
        return a.gpa > b.gpa;
    });
}


int main() {

	std::vector<Student> students = {
		{"Alice Chen",    1001, Year::Freshman,  3.85},
		{"Bob Martinez",  1002, Year::Junior,    2.90},
		{"Carol Davis",   1003, Year::Senior,    3.45},
		{"Dan Okafor",    1004, Year::Sophomore, 3.10},
		{"Eve Park",      1005, Year::Junior,    3.72},
		{"Frank Wilson",  1006, Year::Senior,    2.55},
	};


	print_all(students);

	std::cout << "avg gpa: " << average_gpa(students) << std::endl;

	Student* s = find_by_id(students, 1001);

	s->gpa = 4.0;

	print_all(filter_by_year(students, Year{Year::Junior}));

	sort_by_gpa(students);

	print_all(students);




}