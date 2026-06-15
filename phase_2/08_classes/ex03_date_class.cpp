// Exercise 3: Date Class
//
// Task: Build a Date class that validates and formats dates.
//
// Class definition:
//
//   class Date {
//   public:
//       Date(int year, int month, int day);
//
//       // Getters
//       int year() const;
//       int month() const;
//       int day() const;
//
//       // Formatting
//       std::string to_string() const;            // "2026-06-15"
//       std::string to_long_string() const;       // "June 15, 2026"
//
//       // Comparison
//       bool equals(const Date& other) const;
//       bool is_before(const Date& other) const;
//       bool is_after(const Date& other) const;
//
//       // Operations
//       Date add_days(int days) const;            // return new Date
//       int days_between(const Date& other) const;
//
//       // Queries
//       bool is_leap_year() const;
//       int day_of_year() const;                  // 1-365 (or 366)
//
//       void print() const;
//
//   private:
//       int year_, month_, day_;
//
//       // Helpers
//       static bool is_valid(int y, int m, int d);
//       static int days_in_month(int month, int year);
//       static bool is_leap(int year);
//   };
//
// Validation rules:
//   - Month: 1-12
//   - Day: 1 to days_in_month
//   - If invalid, throw std::invalid_argument with a message
//
// Leap year rules:
//   - Divisible by 4: leap year
//   - Except divisible by 100: not a leap year
//   - Except divisible by 400: leap year
//   - (Same rules you know from any language)
//
// For add_days(): handle month/year rollovers. The simplest approach:
//   - Loop: while remaining days > 0, add one day at a time, rolling
//     over month/year as needed. Not efficient, but simple and correct.
//
// For days_between(): convert both dates to "days since some epoch"
//   and subtract. Or just count days one at a time from the earlier
//   date to the later date.
//
// In main():
//   - Create several dates
//   - Print them in both formats
//   - Compare two dates
//   - Add days (e.g., 100 days from today)
//   - Compute days between two dates
//   - Test leap year
//   - Try creating an invalid date — catch the exception
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_date_class.cpp

// YOUR CODE HERE
