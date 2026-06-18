// Exercise 2: MyString — A Simplified String Class with RAII
//
// Task: Build your own string class that manages a dynamic char array.
//       This teaches you exactly what std::string does under the hood.
//
// Class definition:
//
//   class MyString {
//   public:
//       MyString();                              // default: empty string
//       MyString(const char* str);               // from C-string
//       ~MyString();                             // free the memory
//
//       // Getters
//       int length() const;
//       const char* c_str() const;               // return raw pointer
//       bool empty() const;
//       char at(int index) const;                // bounds-checked access
//
//       // Modifiers
//       void append(const char* str);
//       void clear();
//
//       // Utility
//       void print() const;
//       int find(char c) const;                  // return index or -1
//
//   private:
//       char* data_;        // dynamically allocated char array
//       int length_;        // length (not counting null terminator)
//
//       // Helper
//       void copy_from(const char* str);         // allocate and copy
//   };
//
// Requirements:
//   - Constructor allocates memory with new[]
//   - Destructor frees with delete[]
//   - Store strings as null-terminated char arrays (like C strings)
//   - append() must allocate a new, larger buffer, copy old + new, delete old
//   - Use std::strlen and std::strcpy from <cstring>
//   - Do NOT use std::string anywhere — the point is to manage memory yourself
//
// In main():
//   - Create a MyString from a C-string literal
//   - Print it and its length
//   - Append to it, print again
//   - Test at() with valid and invalid indices
//   - Test find()
//   - Clear it, verify empty
//   - Create a default (empty) MyString, verify it works
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_string_class.cpp

// YOUR CODE HERE

#include <iostream>
#include <cstring>
#include <stdexcept>


class MyString {

public:

	MyString() {
		data_ = new char[0];
		length_ = 0;
	}
	
	MyString(const char* str) {
		length_ = strlen(str);
		data_ = new char[length_];
		strcpy(data_, str);
	}

	~MyString() {
		delete data_;
	}


	// Getters
	int length() const {
		return length_;
	}

	const char* c_str() const {
		return data_;
	}

	bool empty() const {
		return length_ == 0;
	}

	char at(int index) const {
		if (index >= length_ || index < 0) {
			throw std::out_of_range("Index Out of Bounds.");
		}
		return data_[index];
	}

	// Modifiers
	void append(const char* str) {
		// need to delete old buffer and use new to create a new one
		char* old_data = data_;

		data_ = new char[length_ + strlen(str)];

		// copy over existing data
		strcpy(data_, old_data);
		strcpy(data_ + strlen(old_data), str);
		// update the length
		length_ += strlen(str);

	}


	void clear() {
		// string becomes empty string
		delete data_;
		data_ = new char[0];
		length_ = 0;
	}


	// Utility
	void print() const {
		std::cout << data_ << std::endl;
	}


	int find(char c) const {
		int idx = -1;

		for (int i = 0; i < length_; ++i) {
			if (data_[i] == c) {
				idx = i;
				break;
			}
		}

		return idx;

	}





private:
	char* data_;
	int length_;

};



int main() {

	MyString str1; // should create an empty string

	str1.print();

	std::cout << "str1 length(): " << str1.length() << std::endl;	

	std::cout << "str1 empty(): " << (str1.empty() ? "true" : "false") << std::endl;

	MyString str2("This is my string.");

	str2.print();

	std::cout << "str2 length(): " << str2.length() << std::endl;	

	std::cout << "str2 empty(): " << (str2.empty() ? "true" : "false") << std::endl;

	str2.append("123 the end");

	str2.print();

	std::cout << "str2 length(): " << str2.length() << std::endl;

	std::cout << "str2.at(5): " << str2.at(5) << std::endl;

	std::cout << "str2.find('T'): " << str2.find('T') << std::endl;

	std::cout << "str2.find('Z'): " << str2.find('Z') << std::endl;

	str2.clear();

	str2.print();

	std::cout << "str2 length(): " << str2.length() << std::endl;


}

