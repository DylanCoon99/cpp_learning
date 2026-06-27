// Exercise 4: Generic DynamicArray<T>
//
// Task: Take your DynamicArray from step 11 ex05 and make it generic
//       using templates. It should work with any type, not just int.
//
// template <typename T>
// class DynamicArray {
// public:
//     DynamicArray();
//     explicit DynamicArray(int capacity);
//     DynamicArray(std::initializer_list<T> init);
//
//     // Rule of Five
//     ~DynamicArray();
//     DynamicArray(const DynamicArray& other);
//     DynamicArray& operator=(DynamicArray other);   // copy-and-swap
//     DynamicArray(DynamicArray&& other) noexcept;
//     DynamicArray& operator=(DynamicArray&& other) noexcept;
//
//     // Element access
//     T& operator[](int index);
//     const T& operator[](int index) const;
//
//     // Modifiers
//     void push_back(const T& value);
//     void push_back(T&& value);         // move version!
//     T pop_back();
//     void clear();
//
//     // Capacity
//     int size() const;
//     int capacity() const;
//     bool empty() const;
//
//     // Swap
//     void swap(DynamicArray& other) noexcept;
//
//     // Stream
//     friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
//         // Note: friend functions in templates must be defined inline
//         os << "[";
//         for (int i = 0; i < arr.size_; ++i) {
//             if (i > 0) os << ", ";
//             os << arr.data_[i];
//         }
//         os << "]";
//         return os;
//     }
//
// private:
//     T* data_;
//     int size_;
//     int capacity_;
//     void grow();
// };
//
// Key changes from the int version:
//   - Replace int* data_ with T* data_
//   - Replace new int[] with new T[]
//   - Add a T&& (rvalue reference) overload of push_back for move semantics
//   - The << operator must be defined inline inside the class (template friend
//     functions are tricky if defined outside)
//
// The move-aware push_back:
//   void push_back(T&& value) {
//       if (size_ == capacity_) grow();
//       data_[size_] = std::move(value);  // move instead of copy
//       ++size_;
//   }
//   This matters when T is something expensive to copy (like std::string).
//
// In main():
//   DynamicArray<int> ints = {1, 2, 3};
//   ints.push_back(4);
//   std::cout << ints << "\n";
//
//   DynamicArray<std::string> strs;
//   strs.push_back("hello");
//   strs.push_back("world");
//   std::cout << strs << "\n";
//
//   DynamicArray<double> dbls = {1.1, 2.2, 3.3};
//   std::cout << dbls << "\n";
//
//   // Copy and move
//   auto copy = ints;
//   auto moved = std::move(strs);
//   std::cout << "moved: " << moved << "\n";
//   std::cout << "strs empty: " << strs.empty() << "\n";
//
//   // Nested
//   DynamicArray<DynamicArray<int>> nested;
//   nested.push_back(DynamicArray<int>{1, 2});
//   nested.push_back(DynamicArray<int>{3, 4});
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_generic_container.cpp

// YOUR CODE HERE
#include <ostream>
#include <stdexcept>
#include <iostream>


template <typename T>
class DynamicArray {
public:
	// Constructors
	DynamicArray() : data_(new T[0]{}), size_(0), capacity_(0) { }; // default: empty
	explicit DynamicArray(int capacity) : data_(new T[capacity]{}), size_(0), capacity_(capacity) { }; // pre-allocated

	DynamicArray(std::initializer_list<T> init) {
		// DynamicArray a = {1,2,3};
		size_ = init.size();
		capacity_ = size_;

		data_ = new T[capacity_];

		int i = 0;
		for (const T& n : init) {
			data_[i] = n;
			++i;
		}

	}

	// Rule of Five
	~DynamicArray() {
		delete[] data_;
	}

	DynamicArray(const DynamicArray& other) : data_(new T[other.capacity_]{}), size_(other.size_), capacity_(other.capacity_) {
		// copy constructor
		std::copy(other.data_, other.data_ + size_, data_);
	}

	DynamicArray& operator=(const DynamicArray& other) {
		// copy assignment

		// clean up old resource
		delete[] data_;

		// copy the other resource to this one
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = new T[capacity_];

		// copy data in the buffer
		std::copy(other.data_, other.data_ + size_, data_);

		return *this;
	}

	DynamicArray(DynamicArray&& other) noexcept
		: data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	DynamicArray& operator=(DynamicArray&& other) noexcept {
		// move assignment
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = other.data_;

		// clean up the other array
		other.size_ = 0;
		other.capacity_ = 0;

		other.data_ = nullptr;

		return *this;
	}

     // Element access
	T& operator[](int index) {
		if (index > size_ - 1) {
			throw std::runtime_error("Index out of range");
		}
		return data_[index];
	}

	const T& operator[](int index) const {
		if (index > size_ - 1) {
			throw std::runtime_error("Index out of range");
		}
		return data_[index];
	}

	// Modifiers
	void push_back(const T& value) {
		if (size_ == capacity_) grow();
		data_[size_] = value;
		++size_;
	}

	void push_back(T&& value) {
		// move version!
		if (size_ == capacity_) grow();
		data_[size_] = std::move(value); 
		++size_;
	}

	T pop_back() {
		if (size_ == 0) {
			throw std::runtime_error("Array is empty!");
		}
		T ret = data_[size_ - 1];
		--size_;
		return ret;
	}

	void clear() {
		delete[] data_;
		data_ = new T[0];
		size_ = 0;
		capacity_ = 0;
	}

	// Capacity
	int size() const {
		return size_;
	}

	int capacity() const {
		return capacity_;
	}

	bool empty() const {
		return size_ == 0;
	}
	// Swap
	void swap(DynamicArray& other) noexcept {
		DynamicArray<T> temp;
		temp = other;
		other = *this;
		*this = temp;
	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
		// Note: friend functions in templates must be defined inline
		os << "[";
		for (int i = 0; i < arr.size_; ++i) {
			if (i > 0) os << ", ";
			os << arr.data_[i];
		}
			os << "]";
			return os;
	}


private:
	T* data_;
	int size_;
	int capacity_;

	void grow() {
		// double capacity
		T* old_data = data_;
		int new_cap = capacity_ == 0 ? 1 : capacity_ * 2;

		data_ = new T[new_cap];
		capacity_ = capacity_ != 0 ? capacity_ * 2 : 1;
		// copy over existing data
		std::copy(old_data, old_data + size_, data_);

	}


};


int main() {

	// int array
	DynamicArray<int> ints = {1, 2, 3};
	ints.push_back(4);
	ints.push_back(5);
	std::cout << "ints: " << ints << std::endl;
	std::cout << "size: " << ints.size() << ", capacity: " << ints.capacity() << std::endl;

	// pop
	int popped = ints.pop_back();
	std::cout << "popped: " << popped << std::endl;
	std::cout << "ints after pop: " << ints << std::endl;

	// string array
	DynamicArray<std::string> strs;
	strs.push_back("hello");
	strs.push_back("world");
	strs.push_back(std::string("moved in"));
	std::cout << "strs: " << strs << std::endl;

	// double array
	DynamicArray<double> dbls = {1.1, 2.2, 3.3};
	std::cout << "dbls: " << dbls << std::endl;

	// element access
	std::cout << "ints[0]: " << ints[0] << std::endl;
	ints[0] = 99;
	std::cout << "ints[0] after set: " << ints[0] << std::endl;

	// copy
	DynamicArray<int> copy = ints;
	copy.push_back(100);
	std::cout << "copy: " << copy << std::endl;
	std::cout << "ints unchanged: " << ints << std::endl;

	// move
	DynamicArray<std::string> moved = std::move(strs);
	std::cout << "moved: " << moved << std::endl;
	std::cout << "strs empty: " << (strs.empty() ? "true" : "false") << std::endl;

	// move assignment
	DynamicArray<double> d2;
	d2 = std::move(dbls);
	std::cout << "d2: " << d2 << std::endl;
	std::cout << "dbls empty: " << (dbls.empty() ? "true" : "false") << std::endl;

	// clear
	copy.clear();
	std::cout << "copy after clear, empty: " << (copy.empty() ? "true" : "false") << std::endl;

}