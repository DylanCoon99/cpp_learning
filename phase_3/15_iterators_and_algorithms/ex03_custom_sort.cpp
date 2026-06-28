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
