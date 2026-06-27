// Exercise 3: Template Specialization
//
// Task: Practice full and partial template specialization.
//
// Part A — Full specialization of a function template:
//
//   Write a generic to_string:
//     template <typename T>
//     std::string to_string(const T& value);
//       — Default: use std::to_string(value) for numeric types
//
//   Specialize for:
//     template <> std::string to_string<bool>(const bool& value);
//       — return "true" or "false"
//
//     template <> std::string to_string<char>(const char& value);
//       — return a single-character string
//
//     template <> std::string to_string<std::string>(const std::string& value);
//       — return the string itself (std::to_string doesn't work on strings)
//
//   Test: to_string(42), to_string(true), to_string('A'), to_string(std::string("hi"))
//
// Part B — Full specialization of a class template:
//
//   template <typename T>
//   class Formatter {
//   public:
//       static std::string format(const T& value) {
//           return "[" + std::to_string(value) + "]";
//       }
//   };
//
//   Specialize for std::string:
//     template <>
//     class Formatter<std::string> {
//     public:
//         static std::string format(const std::string& value) {
//             return "\"" + value + "\"";
//         }
//     };
//
//   Specialize for bool:
//     Returns "[YES]" or "[NO]"
//
//   Test all: Formatter<int>::format(42), Formatter<std::string>::format("hello"),
//             Formatter<bool>::format(true)
//
// Part C — Partial specialization:
//
//   template <typename T>
//   class Container {
//   public:
//       void store(const T& value);
//       void print() const;
//   private:
//       T value_;
//   };
//
//   Partial specialization for pointers:
//   template <typename T>
//   class Container<T*> {
//       — stores a pointer
//       — print() dereferences and prints the pointed-to value
//       — add is_null() method
//   };
//
//   Partial specialization for vectors:
//   template <typename T>
//   class Container<std::vector<T>> {
//       — stores a vector
//       — print() prints all elements
//       — add size() method
//   };
//
//   Test: Container<int>, Container<int*>, Container<std::vector<int>>
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_specialization.cpp

// YOUR CODE HERE
#include <climits>
#include <iostream>
#include <string>


// Part A
template <typename T>
std::string to_string(const T& value) {
	return std::to_string(value);
}

template <> 
std::string to_string<bool>(const bool& value) {
	return value ? "true" : "false";
}

template <> 
std::string to_string<char>(const char& value) {
	std::string ret(1, value);
	return ret;
}

template <>
std::string to_string(const std::string& value) {
	return value;
}



// Part B
template <typename T>
class Formatter {
public:
	static std::string format(const T& value) {
		return "[" + std::to_string(value) + "]";
	}
};


template <>
class Formatter<std::string> {
public:
	static std::string format(const std::string& value) {
		return "\"" + value + "\"";
	}
};



template <>
class Formatter<bool> {
public:
	static std::string format(const bool value) {
		return value ? "[YES]" : "[NO]";
	}
};



// Part C
template <typename T>
class Container {
public:
	void store(const T& value) {
		value_ = value;
	}
	void print() const {
		std::cout << value_ << std::endl;
	}
private:
	T value_;
};


template <typename T>
class Container <T*> {
public:
	void store(T* value) {
		value_ = value;
	}
	void print() const {
		std::cout << *value_ << std::endl;
	}

	bool is_null() {
		return value_ == nullptr;
	}
private:
	T* value_;
};


template <typename T>
class Container <std::vector<T>> {
public:
	void store(const std::vector<T>& value) {
		value_ = value;
	}
	void print() const {
		for (auto &v : value_) {
			std::cout << v << " ";
		}
		std::cout << std::endl;
	}

	int size() {
		return value_.size();
	}

private:
	std::vector<T> value_;
};



int main() {

	// Part A Test
	{
		std::cout << to_string(42) << std::endl;
		std::cout << to_string(true) << std::endl;
		std::cout << to_string('A') << std::endl;
		std::cout << to_string(std::string("hi")) << std::endl;
	}

	// Part B Test
	{
		std::cout << "Formatter<int>::format(42): " << Formatter<int>::format(42) << std::endl;
		std::cout << "Formatter<std::string>::format(\"hello\"): " << Formatter<std::string>::format("hello") << std::endl;
		std::cout << "Formatter<bool>::format(true): " << Formatter<bool>::format(true) << std::endl;
	}

	// Part C Test
	{
		Container<int> c1;
		c1.store(42);
		std::cout << "Container<int>: ";
		c1.print();

		int x = 99;
		Container<int*> c2;
		c2.store(&x);
		std::cout << "Container<int*>: ";
		c2.print();
		std::cout << "is_null: " << (c2.is_null() ? "true" : "false") << std::endl;

		Container<std::vector<int>> c3;
		std::vector<int> v = {10, 20, 30, 40, 50};
		c3.store(v);
		std::cout << "Container<vector<int>>: ";
		c3.print();
		std::cout << "size: " << c3.size() << std::endl;
	}
}
