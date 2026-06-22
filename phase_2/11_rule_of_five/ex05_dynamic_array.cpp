// Exercise 5: DynamicArray — A Complete Resizable Array
//
// Task: Build a production-quality dynamic array (simplified std::vector)
//       with full Rule of Five, operator overloading, and proper memory
//       management. This pulls together everything from Phase 2.
//
// Class definition:
//
//   class DynamicArray {
//   public:
//       // Constructors
//       DynamicArray();                              // default: empty
//       explicit DynamicArray(int capacity);          // pre-allocated
//       DynamicArray(std::initializer_list<int> init); // DynamicArray a = {1,2,3};
//
//       // Rule of Five
//       ~DynamicArray();
//       DynamicArray(const DynamicArray& other);
//       DynamicArray& operator=(const DynamicArray& other);
//       DynamicArray(DynamicArray&& other) noexcept;
//       DynamicArray& operator=(DynamicArray&& other) noexcept;
//
//       // Element access
//       int& operator[](int index);
//       const int& operator[](int index) const;
//       int& at(int index);                          // bounds-checked
//       const int& at(int index) const;
//       int& front();
//       int& back();
//
//       // Capacity
//       int size() const;
//       int capacity() const;
//       bool empty() const;
//       void reserve(int new_cap);                   // grow capacity
//       void shrink_to_fit();                        // reduce capacity to size
//
//       // Modifiers
//       void push_back(int value);
//       int pop_back();
//       void insert(int index, int value);
//       void erase(int index);
//       void clear();
//       void resize(int new_size, int fill = 0);
//
//       // Comparison
//       bool operator==(const DynamicArray& other) const;
//       bool operator!=(const DynamicArray& other) const;
//
//       // Stream
//       friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr);
//
//       // Swap
//       void swap(DynamicArray& other) noexcept;
//
//   private:
//       int* data_;
//       int size_;
//       int capacity_;
//
//       void grow();   // double capacity
//   };
//
// Requirements:
//   - Use copy-and-swap for copy assignment
//   - Move operations must be noexcept
//   - reserve() only grows, never shrinks
//   - push_back calls grow() when full
//   - insert/erase shift elements as needed
//   - Stream output: [1, 2, 3, 4, 5]
//   - at() throws std::out_of_range
//   - All Rule of Five functions must be correct (no double-free, no leaks)
//
// In main():
//   - Create arrays with each constructor
//   - Test push_back, pop_back, insert, erase
//   - Test copy construction and assignment
//   - Test move construction and assignment
//   - Put DynamicArrays in a std::vector<DynamicArray> — this stress-tests
//     your copy/move operations
//   - Test initializer_list: DynamicArray a = {10, 20, 30};
//   - Print everything with <<
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_dynamic_array.cpp

// YOUR CODE HERE
#include <ostream>
#include <stdexcept>
#include <iostream>


class DynamicArray {
public:
	// Constructors
	DynamicArray() : data_(new int[0]{}), size_(0), capacity_(0) { }; // default: empty
	explicit DynamicArray(int capacity) : data_(new int[capacity]{}), size_(0), capacity_(capacity) { }; // pre-allocated

	DynamicArray(std::initializer_list<int> init) {
		// DynamicArray a = {1,2,3};
		size_ = init.size();
		capacity_ = size_;

		data_ = new int[capacity_];

		int i = 0;
		for (const int& n : init) {
			data_[i] = n;
			++i;
		}

	}

	// Rule of Five
	~DynamicArray() {
		delete[] data_;
	}

	DynamicArray(const DynamicArray& other) : data_(new int[other.capacity_]{}), size_(other.size_), capacity_(other.capacity_) {
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
		data_ = new int[capacity_];

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
	int& operator[](int index) {
		// bounds-checked
		if (index > size_ - 1) {
			throw std::out_of_range("Index Out of Bounds.");
		}
		return data_[index];
	}

	const int& operator[](int index) const {
		// bounds-checked
		if (index > size_ - 1) {
			throw std::out_of_range("Index Out of Bounds.");
		}
		return data_[index];
	}

	int& at(int index) {
		// bounds-checked
		if (index > size_ - 1) {
			throw std::out_of_range("Index Out of Bounds.");
		}
		return data_[index];
	}

	const int& at(int index) const {
		// bounds-checked
		if (index > size_ - 1) {
			throw std::out_of_range("Index Out of Bounds.");
		}
		return data_[index];
	}

	int& front() {
		if (empty()) {
			throw std::out_of_range("Array is empty.");
		}
		return data_[0];
	}

	int& back() {
		if (empty()) {
			throw std::out_of_range("Array is empty.");
		}
		return data_[size_ - 1];
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
	void reserve(int new_cap) {
		if (new_cap <= capacity_) {
			throw std::runtime_error("New capacity must be greater than current capacity!");
		}

		// grow capacity
		int* old_data = data_;

		data_ = new int[new_cap];

		// copy over existing data
		std::copy(old_data, old_data + size_, data_);

	}
	void shrink_to_fit() {
		// reduce capacity to size
		capacity_ = size_;

		int* old_data = data_;
		data_ = new int[capacity_];

		std::copy(old_data, old_data + size_, data_);

	}
	// Modifiers
	void push_back(int value) {
		// check if there is enough capacity
		if (size_ == capacity_) {
			grow();
		}
		data_[size_] = value;
		++size_;
	}

	int pop_back() {
		int popped = data_[size_ - 1];
		--size_;
		return popped;
	}

	void insert(int index, int value) {
		if (capacity_ == size_) grow();

		int next;

		for (int i = index; i <= size_; ++i) {
			next = data_[i];
			if (i == index) {
				data_[i] = value;
			} else {
				data_[i] = next;
			}

		}

		++size_;
	}

	void erase(int index) {
		if (index > size_ - 1) {
			throw std::out_of_range("Array is empty.");
		}
		for (int i = index; i < size_; ++i) {
			if (i != size_ - 1) {
				data_[i] = data_[i + 1];
			}
		}
		--size_;
	}

	void clear() {
		delete[] data_;
		data_ = new int[0];
		size_ = 0;
		capacity_ = 0;
	}

	void resize(int new_size, int fill = 0) {
		if (new_size > size_) {
			// initialize new_size - size_ elements as 0
			// have to make sure the capacity is big enough
			if (capacity_ < new_size) grow();

			for (int i = size_; i < new_size; ++i) {
				data_[i] = fill;
			}

		}

		size_ = new_size;
	}

	// Comparison
	bool operator==(const DynamicArray& other) const {
		if (size_ != other.size_) return false;

		// check if the arrays are equal
		for (int i = 0; i < size_; ++i) {
			if (data_[i] != other.data_[i]) {
				return false;
			}
		}
		
		return true;
	}

	bool operator!=(const DynamicArray& other) const {
		return !(*this == other);
	}

	// Stream
	friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
		for (int i = 0; i < arr.size_; ++i) {
			os << arr[i] << " ";
		}
		return os;
	}

	// Swap
	void swap(DynamicArray& other) noexcept {
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
		std::swap(data_, other.data_);
	}

private:
	int* data_;
	int size_;
	int capacity_;

	void grow() {
		// double capacity
		int* old_data = data_;

		data_ = new int[capacity_ * 2];
		capacity_ = capacity_ != 0 ? capacity_ * 2 : 1;
		// copy over existing data
		std::copy(old_data, old_data + size_, data_);
		
	}
};


int main() {

	// Default constructor
	DynamicArray a;
	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	a.push_back(40);
	std::cout << "a: " << a << std::endl;
	std::cout << "a.size(): " << a.size() << std::endl;
	std::cout << "a.capacity(): " << a.capacity() << std::endl;


	
	// Pre-allocated constructor
	DynamicArray b(10);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	std::cout << "b: " << b << std::endl;
	std::cout << "b.size(): " << b.size() << std::endl;
	std::cout << "b.capacity(): " << b.capacity() << std::endl;

	// Initializer list constructor
	DynamicArray c = {5, 10, 15, 20, 25};
	std::cout << "c: " << c << std::endl;
	
	// Element access
	std::cout << "a[0]: " << a[0] << std::endl;
	std::cout << "a.at(2): " << a.at(2) << std::endl;
	std::cout << "a.front(): " << a.front() << std::endl;
	std::cout << "a.back(): " << a.back() << std::endl;

	// Pop
	int popped = a.pop_back();
	std::cout << "popped: " << popped << std::endl;
	std::cout << "a after pop: " << a << std::endl;
	
	// Erase
	a.erase(1);
	std::cout << "a after erase(1): " << a << std::endl;

	// Resize
	a.resize(6, 99);
	std::cout << "a after resize(6, 99): " << a << std::endl;

	// Clear
	b.clear();
	std::cout << "b after clear, empty: " << (b.empty() ? "true" : "false") << std::endl;

	// Copy constructor
	DynamicArray d = c;
	std::cout << "d (copy of c): " << d << std::endl;
	d.push_back(100);
	std::cout << "c unchanged: " << c << std::endl;
	std::cout << "d modified: " << d << std::endl;

	// Copy assignment
	DynamicArray e(4);
	e.push_back(77);
	e = c;
	std::cout << "e (assigned from c): " << e << std::endl;

	// Move constructor
	DynamicArray f = std::move(c);
	std::cout << "f (moved from c): " << f << std::endl;
	std::cout << "c after move, empty: " << (c.empty() ? "true" : "false") << std::endl;
	
	// Move assignment
	DynamicArray g;
	g = std::move(f);
	std::cout << "g (move assigned from f): " << g << std::endl;
	std::cout << "f after move, empty: " << (f.empty() ? "true" : "false") << std::endl;
	
	// Comparison
	DynamicArray h = {5, 10, 15, 20, 25};
	std::cout << "g == h: " << (g == h ? "true" : "false") << std::endl;
	std::cout << "g != d: " << (g != d ? "true" : "false") << std::endl;

	// Stress test: push into vector
	std::vector<DynamicArray> vec;
	vec.push_back(DynamicArray{1, 2, 3});
	vec.push_back(DynamicArray{4, 5, 6});
	vec.push_back(DynamicArray{7, 8, 9});
	for (const auto& arr : vec) {
		std::cout << arr << std::endl;
	}

	

}
