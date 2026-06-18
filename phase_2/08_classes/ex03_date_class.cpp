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
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>


class Date {

public:
	Date(int year, int month, int day) {
		if (is_valid(year, month, day)) {
			year_  = year;
			month_ = month;
			day_   = day;
		} else {
			throw std::invalid_argument("Invalid Date!");
		}
	}

	// Getters
	int year() const {
		return year_;
	}

	int month() const {
		return month_;
	}

	int day() const {
		return day_;
	}


	// Formatting
	std::string to_string() const {
      return std::to_string(year_) + "-" + std::to_string(month_) + "-" + std::to_string(day_);                                                                                      
  	}   
	

	std::string to_long_string() const {
		// "June 15, 2026"
		std::string month_str;

		switch(month_) {
		case 1:
			month_str = "January"; break;
		case 2:
			month_str = "February"; break;
		case 3:
			month_str = "March"; break;
		case 4:
			month_str = "April"; break;
		case 5:
			month_str = "May"; break;
		case 6:
			month_str = "June"; break;
		case 7:
			month_str = "July"; break;
		case 8:
			month_str = "August"; break;
		case 9:
			month_str = "September"; break;
		case 10:
			month_str = "October"; break;
		case 11:
			month_str = "November"; break;
		case 12:
			month_str = "December"; break;
		}

		return month_str + " " + std::to_string(day_) + ", " + std::to_string(year_);

	}

	// Comparison
	bool equals(const Date& other) const {
		return (year_ == other.year()) && (month_ == other.month()) && (day_ == other.day());
	}

	bool is_before(const Date& other) const {
		// if this is before other
		if (year_ < other.year()) {
			return true;
		} else if (year_ == other.year()) {
			// check the month
			if (month_ < other.month()) {
				return true;
			} else if (month_ == other.month()) {
				if (day_ < other.day()) {
					return true;
				}
			}
		}
		return false;
	}

	bool is_after(const Date& other) const {
		// if this is after other
		if (year_ > other.year()) {
			return true;
		} else if (year_ == other.year()) {
			// check the month
			if (month_ > other.month()) {
				return true;
			} else if (month_ == other.month()) {
				if (day_ > other.day()) {
					return true;
				}
			}
		}
		return false;
	}

	// Operations
	Date add_days(int days) const {
		int remaining_days = days;
		int current_month = month_;
		int current_year  = year_;
		int current_day   = day_;

		while (remaining_days > 0) {
			// check to make sure the month is updated correctly (should not exceed number of days in that month)
			if (days_in_month(current_month, current_year) == current_day) {
				// roll over to next month
				current_month = (current_month + 1) % 12;
				current_day = 1;
				if (current_month == 1) {
					++current_year;
				}
			} else {
				++current_day;
			}
			--remaining_days;
		}

		// create a new date object
		return Date(current_year, current_month, current_day);


	}

	int days_between(const Date& other) const {
		
		return abs(to_days() - other.to_days());

	}

	// Queries
	bool is_leap_year() const {
		return is_leap(year_);
	}
	int day_of_year() const {
		int day_of_year = 0;
		for (int i = 1; i < month(); ++i) {
			day_of_year += days_in_month(i, year());
		}

		day_of_year += day_;

		return day_of_year;
	}

	void print() const {
		std::cout << to_string() << std::endl;
	}




private:

	int year_, month_, day_;

	// Helpers
	static bool is_valid(int y, int m, int d) {


		bool valid_day = (d <= days_in_month(m, y) && (d > 0));
		bool valid_month = (m <= 12) && (m > 0);
		bool valid_year = (y > 0);

		return valid_day && valid_month && valid_year;
	}

	static int days_in_month(int month, int year) {
		
		bool leap = is_leap(year);

		switch(month) {
		case(1):
			return 31; break;
		case(2):
			if (leap) {
				return 29; break;
			}
			return 28; break;
		case(3):
			return 31; break;
		case(4):
			return 30; break;
		case(5):
			return 31; break;
		case(6):
			return 30; break;
		case(7):
			return 31; break;
		case(8):
			return 31; break;
		case(9):
			return 30; break;
		case(10):
			return 31; break;
		case(11):
			return 30; break;
		case(12):
			return 31; break;
		}
		return -1;
	}
	static bool is_leap(int year) {
		// Leap year rules:
		//   - Divisible by 4: leap year
		//   - Except divisible by 100: not a leap year
		//   - Except divisible by 400: leap year
		//   - (Same rules you know from any language)
		if (year % 4 == 0) {
			if (year % 100 == 0) {
				// if it's a century -> only a leap year if divisible by 400
				if (year % 400 == 0) {
					return true;
				}
				return false;
			}
			return true;
		}
		return false;
	}

	int to_days() const {                                                                                                                                                              
		int days = 0;
		for (int y = 1; y < year_; ++y)                                                                                                                                                
			days += is_leap(y) ? 366 : 365;                                                                                                                                          
		days += day_of_year();                                                                                                                                                         
		return days;
	  }    


};


int main() {


//   - Create several dates
	Date date1 = Date(2026, 6, 17);
	Date date2 = Date(2026, 6, 18);
	Date date3 = Date(2025, 6, 17);
//   - Print them in both formats
	date1.print();
	date2.print();
	date3.print();
//   - Compare two dates
	std::cout << "Days between date1 and date3: " << date1.days_between(date3) << std::endl;
//   - Add days (e.g., 100 days from today)
	Date new_date = date1.add_days(100);
	new_date.print();
//   - Compute days between two dates
	std::cout << "Days between: " << date1.days_between(new_date) << std::endl;
//   - Test leap year
	std::cout << "Is leap year: " << date1.is_leap_year() << std::endl; 
//   - Try creating an invalid date — catch the exception
	Date(2020, 13, 54);


}