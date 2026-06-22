// Exercise 2: Move Semantics — MyString
//
// Task: Add move constructor and move assignment to MyString.
//       This builds on exercise 1 (copy semantics must also work).
//
// Add to MyString:
//
//   // Move constructor — steal resources
//   MyString(MyString&& other) noexcept;
//
//   // Move assignment — steal resources, clean up old
//   MyString& operator=(MyString&& other) noexcept;
//
// Requirements:
//   - Move constructor: steal the pointer and size, set source to null/0
//   - Move assignment: free old data, steal, null out source
//   - Both must be noexcept
//   - After moving, the source must be in a valid state (safe to destroy,
//     but contents are unspecified)
//
// Also add a helper to observe moves:
//   - Add print statements (or a flag) in the copy/move constructors
//     so you can SEE which one gets called:
//       MyString(const MyString& other) {
//           std::cout << "COPY constructor\n";
//           // ...
//       }
//       MyString(MyString&& other) noexcept {
//           std::cout << "MOVE constructor\n";
//           // ...
//       }
//
// Write a function that returns a MyString:
//   MyString make_greeting(const char* name) {
//       MyString s("Hello, ");
//       s.append(name);
//       s.append("!");
//       return s;   // will this copy or move?
//   }
//
// In main():
//   - Create a MyString
//   - Copy it (should print "COPY constructor")
//   - Move it with std::move (should print "MOVE constructor")
//   - Verify the moved-from object is empty
//   - Call make_greeting — observe whether copy or move is used
//     (usually the compiler elides the copy entirely via NRVO —
//      Named Return Value Optimization — but it's good to see)
//   - Create a vector<MyString>, push_back several strings
//     When the vector reallocates, it will MOVE elements if your
//     move constructor is noexcept, or COPY if it isn't.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_move_semantics.cpp

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
	MyString(const MyString& other) : data_(new char[other.length_]{}), length_(other.length_) {
		// copy the data in other to this new instance
		std::cout << "COPY constructor\n";
		std::copy(other.data_, other.data_ + other.length(), data_);
	}


	// Move constructor — steal resources
	MyString(MyString&& other) noexcept 
		: data_(other.data_), length_(other.length_)  {
		std::cout << "MOVE constructor\n";
		// After a move, the source object must be in a valid but unspecified state — safe to destroy, but don't use its data.

		other.data_ = nullptr;
		other.length_ = 0;
	}

	// Move assignment — steal resources, clean up old
	MyString& operator=(MyString&& other) noexcept {
		std::cout << "MOVE assignment\n";
		if (this == &other) return *this;

		delete[] data_;

		data_ = other.data_;
		length_ = other.length_;

		other.data_ = nullptr;
		other.length_ = 0;

		return *this;
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
		if (data_) {
			std::cout << data_ << std::endl;
		}
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
		std::cout << "COPY assignment\n";
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


MyString make_greeting(const char* name) {
	MyString s("Hello, ");
	s.append(name);
	s.append("!");
	return s;   // will this copy or move?
}




int main() {

	//   - Create a MyString
	MyString str1("This is my first string.");
	//   - Copy it (should print "COPY constructor")
	MyString str2 = str1;
	//   - Move it with std::move (should print "MOVE constructor")
	MyString str3 = std::move(str1);
	//   - Verify the moved-from object is empty
	str1.print();
	//   - Call make_greeting — observe whether copy or move is used
	//     (usually the compiler elides the copy entirely via NRVO —
	//      Named Return Value Optimization — but it's good to see)
	MyString str4 = make_greeting("dylan");
	//   - Create a vector<MyString>, push_back several strings
	//     When the vector reallocates, it will MOVE elements if your
	//     move constructor is noexcept, or COPY if it isn't.
	std::vector<MyString> strings;
	strings.push_back(str2);
	strings.push_back(str3);
	strings.push_back(str4);



}
