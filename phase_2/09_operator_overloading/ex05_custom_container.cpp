// Exercise 5: Custom Container — SortedList
//
// Task: Build a sorted integer list that maintains elements in ascending
//       order. This exercises [], (), ++, <<, and comparison operators.
//
// Class definition:
//
//   class SortedList {
//   public:
//       SortedList() = default;
//       SortedList(std::initializer_list<int> init);  // SortedList s = {5,2,8,1};
//
//       // Element access
//       const int& operator[](int index) const;    // bounds-checked
//
//       // Functor: operator() as a "contains" check
//       bool operator()(int value) const;           // list(42) returns true if 42 is in list
//
//       // Insert (maintains sorted order)
//       SortedList& operator+=(int value);          // list += 5;
//       SortedList& operator+=(const SortedList& other);  // merge two lists
//
//       // Remove first occurrence
//       SortedList& operator-=(int value);          // list -= 5;
//
//       // Comparison (lexicographic)
//       bool operator==(const SortedList& rhs) const;
//       bool operator!=(const SortedList& rhs) const;
//       bool operator<(const SortedList& rhs) const;
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const SortedList& s);
//
//       // Info
//       int size() const;
//       bool empty() const;
//
//   private:
//       std::vector<int> data_;  // always kept sorted
//
//       void insert_sorted(int value);
//   };
//
// Requirements:
//   - initializer_list constructor should sort the input
//   - operator+= inserts in the correct sorted position (don't append+re-sort)
//     Use std::lower_bound to find the insertion point:
//       #include <algorithm>
//       auto it = std::lower_bound(data_.begin(), data_.end(), value);
//       data_.insert(it, value);
//   - operator() is a functor — using the object like a function call
//     to check membership. Use std::binary_search since data is sorted:
//       return std::binary_search(data_.begin(), data_.end(), value);
//   - Stream output format: [1, 3, 5, 7, 9]
//   - Merging two SortedLists should produce a sorted result
//
// In main():
//   - Create a list from initializer_list
//   - Insert elements with +=
//   - Print with <<
//   - Check membership with (): if (list(42)) { ... }
//   - Access elements with []
//   - Remove with -=
//   - Merge two lists
//   - Compare two lists
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_custom_container.cpp

// YOUR CODE HERE
#include <iostream>


class SortedList {
public:
	SortedList() = default;
	SortedList(std::initializer_list<int> init) {
		// SortedList s = {5,2,8,1};
		// iterate over the init list and insert in ascending order
		for (int value : init) {
			insert_sorted(value);
		}

	}

	// Element access
	const int& operator[](int index) const {
		// bounds-checked

		if (index > size() - 1) {
			throw std::out_of_range("Index out of range!");
		}

		return data_[index];
	}

	// Functor: operator() as a "contains" check
	bool operator()(int value) const {
		// list(42) returns true if 42 is in list
		for (int val : data_) {
			if (val == value) {
				return true;
			}
		}
		return false;
	}

	// Insert (maintains sorted order)
	SortedList& operator+=(int value) {
		// list += 5;
		insert_sorted(value);
		return *this;
	}

	SortedList& operator+=(const SortedList& other) {
		// merge two lists
		for (int idx = 0; idx < other.size(); ++idx) {
			insert_sorted(other[idx]);
		}
		return *this;
	}

	// Remove first occurrence
	SortedList& operator-=(int value) {
		// list -= 5;
		auto it = std::find(data_.begin(), data_.end(), value);

	    // Ensure the value exists before erasing
	    if (it != data_.end()) {
	        data_.erase(it);
	    }
	    return *this;
	}

	// Comparison (lexicographic)
	bool operator==(const SortedList& rhs) const {
		if (size() == rhs.size()) {
			// check each element
			for (int i = 0; i < static_cast<int>(data_.size()); ++i) {
				if (data_[i] != rhs[i]) {
					return false;
				}
			}
		} else {
			return false;
		}
		return true;
	}

	bool operator!=(const SortedList& rhs) const {
		return !(*this == rhs);
	}

	bool operator<(const SortedList& rhs) const {
		return data_ < rhs.data_; 
	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const SortedList& s) {
		for (auto i : s.data_) {
			os << i << " ";
		}
		os << std::endl;
		return os;
	}

	// Info
	int size() const {
		return data_.size();
	}
	bool empty() const {
		return size() == 0;
	}

private:
	std::vector<int> data_;  // always kept sorted

	void insert_sorted(int value) {
		// iterate over the list until the next value is >= value

		// find the index to insert at
		int idx = 0;
		for (int i = 0; i < static_cast<int>(data_.size()); ++i) {
			if (data_[i] < value) {
				++idx;
			}
			else {
				break;
			}
		}
		data_.insert(data_.begin() + idx, value);
	}

};


int main() {

	//   - Create a list from initializer_list
	SortedList l1 = {3, 2, 1, 4, 7, 8, 9, 5, 6};
	SortedList l2 = {14, 12, 13, 11};
	std::cout << l1 << std::endl;
	l1 -= 3;
	l1 += 0;
	std::cout << l1 << std::endl;
	if (l1(9)) {
		std::cout << "It's working!" << std::endl;
	}
	//   - Access elements with []
	std::cout << "l1[3]: " << l1[3] << std::endl;	
	//std::cout << "l1[10]: " << l1[10] << std::endl;	
	//   - Merge two lists
	l1 += l2;
	std::cout << l1 << std::endl;	
	//   - Compare two lists
	std::cout << "l1 == l2: " << (l1 == l2 ? "true" : "false") << std::endl;
	std::cout << "l1 < l2: " << (l1 < l2 ? "true" : "false") << std::endl;
	std::cout << "l1 != l2: " << (l1 != l2 ? "true" : "false") << std::endl;

}