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
