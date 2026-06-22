// Exercise 3: Rule of Five — Stack
//
// Task: Take your Stack class from step 08 ex04 (which had copy/move
//       deleted) and implement the full Rule of Five.
//
// Implement all five:
//
//   ~Stack();                                    // already done
//   Stack(const Stack& other);                   // deep copy
//   Stack& operator=(const Stack& other);        // copy assignment
//   Stack(Stack&& other) noexcept;               // move
//   Stack& operator=(Stack&& other) noexcept;    // move assignment
//
// Also add:
//   void swap(Stack& other) noexcept;
//   Use copy-and-swap for copy assignment if you like.
//
// Requirements:
//   - Copy: allocate new array, copy elements (not just the pointer)
//   - Copy must copy size_, capacity_, AND the data contents
//   - Move: steal pointer, null out source
//   - Move must be noexcept
//   - Self-assignment must work
//
// In main():
//   - Create a stack, push some values
//   - Copy construct: Stack b = a;
//   - Verify both work independently (push to one, doesn't affect other)
//   - Copy assign: b = a;
//   - Move construct: Stack c = std::move(a);
//   - Verify a is now empty
//   - Move assign: b = std::move(c);
//   - Push stacks into a vector<Stack> — this requires working copy or move
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_rule_of_five_stack.cpp

// YOUR CODE HERE
#include <iostream>
#include <type_traits>




class Stack {
public:

	explicit Stack(int capacity = 16) : capacity_(capacity) {
		data_ = new int[capacity_];
		size_ = 0;
	}


	Stack(const Stack& other) 
		: data_(new int[other.capacity_]{}), size_(other.size_), capacity_(other.capacity_){
		// deep copy
		std::copy(other.data_, other.data_ + size_, data_);
	}

	Stack& operator=(const Stack& other) {
		// this is for when this object already exists

		// copy assignment
		if (this == &other) return *this;

		// free the old data
		delete[] data_;

		data_ = new int[capacity_];
		size_ = other.size_;
		capacity_ = other.capacity_;

		std::copy(other.data_, other.data_ + size_, data_);

		return *this;
	}

	Stack(Stack&& other) noexcept {
		// move
		data_ = other.data_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;

	}

	Stack& operator=(Stack&& other) noexcept {
		// move assignment
		if (this == &other) return *this;

		delete[] data_;

		data_ = other.data_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;

		return *this;
	}

	~Stack() {
		std::cout << "Destructor is running." << std::endl;
		delete[] data_;
		std::cout << "Destructor is done." << std::endl;
	}

	void swap(Stack& other) noexcept {
		std::swap(size_, other.size_);
		std::swap(data_, other.data_);
		std::swap(capacity_, other.capacity_);
	}


	void push(int value) {

		if (full()) {
			grow();
		}

		data_[size_] = value;
		++size_;
	}


	int pop() {

		if (empty()) {
			throw std::underflow_error("Stack is empty");
		}

		int val = data_[size_ - 1];
		--size_;
		return val;
	}


	int peek() const {

		if (empty()) {
			throw std::underflow_error("Stack is empty");
		}

		return data_[size_ - 1];
	}


	int size() const {
		return size_;
	}


	int capacity() const {
		return capacity_;
	}


	bool empty() const {
		return size_ == 0;
	}


	bool full() const {
		return capacity_ == size_;
	}


	void print() const {
		// print all elements bottom to top
		for (int i = 0; i < size_; ++i) {
			std::cout << data_[i] << std::endl;
		}
		std::cout << std::endl;
	}



private:
	int* data_;
	int size_;
	int capacity_;

	void grow() {
		// double capacity when full
		int* old_data = data_;

		data_ = new int[capacity_ * 2];
		capacity_ *= 2;

		// copy over existing data
		std::copy(old_data, old_data + size_, data_);
		
	}
};


int main() {

	//   - Create a stack, push some values
	Stack a = Stack{};
	a.push(5);
	a.push(1);
	a.push(2);
	a.push(3);
	//   - Copy construct: Stack b = a;
	Stack b = a;
	//   - Verify both work independently (push to one, doesn't affect other)
	b.push(6);
	a.push(7);
	a.print();
	b.print();
	//   - Copy assign: b = a;
	b = a;
	//   - Move construct: Stack c = std::move(a);
	Stack c = std::move(a);
	//   - Verify a is now empty
	std::cout << "a.empty(): " << (a.empty() ? "true" : "false") << std::endl;
	//   - Move assign: b = std::move(c);
	b = std::move(c);
	//   - Push stacks into a vector<Stack> — this requires working copy or move
	std::vector<Stack> my_stacks;
	my_stacks.push_back(a);
	my_stacks.push_back(b);
	my_stacks.push_back(c);


	for (auto& stack : my_stacks) {
		stack.print();
	}
	


}
