// Exercise 1: Deep Copy — Fix MyString
//
// Task: Take your MyString class from step 08 ex02 and add proper
//       copy semantics. Without them, copying a MyString causes a
//       double-free crash.
//
// Add to MyString:
//
//   // Copy constructor — deep copy
//   MyString(const MyString& other);
//
//   // Copy assignment — deep copy with cleanup
//   MyString& operator=(const MyString& other);
//
// Requirements:
//   - Copy constructor: allocate new memory, copy the characters
//   - Copy assignment: free old memory, allocate new, copy
//   - Handle self-assignment in operator= (what if a = a?)
//   - After copying, both objects must be fully independent
//     (modifying one doesn't affect the other)
//
// Also add:
//   - operator<< for easy printing
//   - operator== to compare two MyStrings
//
// In main():
//   - Create a MyString
//   - Copy construct another: MyString b = a;
//   - Modify a, verify b is unchanged (proves deep copy)
//   - Copy assign: b = a;
//   - Self-assign: a = a; (should not crash)
//   - Put MyStrings in a vector — this triggers copy constructor
//     when the vector reallocates. Without proper copy semantics,
//     this would crash.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_deep_copy.cpp

// YOUR CODE HERE
#include <iostream>
#include <algorithm>


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


	// Copy Constructor
	MyString(const MyString& other) : length_(other.length_), data_(new char[other.length_]{}) {
		// copy the data in other to this new instance
		

		std::copy(other.data_, other.data_ + other.length(), data_);
	}


	~MyString() {
		delete[] data_;
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
		delete[] data_;
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

	// Copy Assignment Operator
	MyString& operator=(const MyString& other) {
		// Assigns an existing object from another. Must handle self-assignment and clean up old resources:

		if (this == &other) return *this;

		delete[] data_; // free the data for the existing resource
		length_ = other.length_;
		data_ = new char[length_];
		std::copy(other.data_, other.data_ + length_, data_);

		return *this;
	}

	bool operator==(MyString& other) {

		if (length_ == other.length_) {
			for (int i = 0; i < length_; ++i) {
				if (data_[i] != other.data_[i]) {
					return false;
				}
			}
		} else {
			return false;
		}
		return true;
	}



	// Stream output (friend)
	friend std::ostream& operator<<(std::ostream& os, MyString& s) {
		os << s.data_ << std::endl;
    	return os; 
	}


private:
	char* data_;
	int length_;

};



int main() {

	//   - Create a MyString
	//   - Copy construct another: MyString b = a;
	MyString str1("this is my first string");
	MyString str2 = str1;  // should use the copy constructor
	//   - Modify a, verify b is unchanged (proves deep copy)
	str1.append(" appending to the end"); // shouldn't affect str2
	str2.print();
	//   - Copy assign: b = a;
	MyString str3("This is my third string");
	str3.print();
	str3 = str1;
	str3.print();
	//   - Self-assign: a = a; (should not crash)
	str1 = str1;
	//   - Put MyStrings in a vector — this triggers copy constructor
	std::vector<MyString> strings = {str1, str2, str3};
	for (auto& str : strings) {
		std::cout << str;
	} 

}