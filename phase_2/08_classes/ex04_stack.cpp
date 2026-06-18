// Exercise 4: RAII Stack
//
// Task: Build a stack data structure backed by a dynamic array.
//       This exercises RAII: the constructor allocates, the destructor frees.
//
// Class definition:
//
//   class Stack {
//   public:
//       explicit Stack(int capacity = 16);     // initial capacity
//       ~Stack();                              // free the array
//
//       // Deleted — no copying (we'll add this in step 11)
//       Stack(const Stack&) = delete;
//       Stack& operator=(const Stack&) = delete;
//
//       void push(int value);
//       int pop();                             // remove and return top
//       int peek() const;                      // return top without removing
//
//       int size() const;
//       int capacity() const;
//       bool empty() const;
//       bool full() const;
//
//       void print() const;                    // print all elements bottom to top
//
//   private:
//       int* data_;
//       int size_;
//       int capacity_;
//
//       void grow();   // double capacity when full
//   };
//
// Requirements:
//   - push(): if full, call grow() to double the capacity
//   - grow(): allocate new array (2x), copy elements, delete old, update pointer
//   - pop() and peek(): throw std::underflow_error if empty
//   - Use = delete to prevent copying (we'll fix this in step 11)
//   - Constructor uses new[], destructor uses delete[]
//
// In main():
//   - Create a stack with small initial capacity (e.g., 4)
//   - Push elements beyond initial capacity — verify it grows
//   - Print size and capacity after each push to see growth
//   - Pop elements and print them
//   - Try popping from empty stack — catch the exception
//   - Demonstrate RAII: create a stack in a block {}, verify destructor runs
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_stack.cpp

// YOUR CODE HERE
#include <iostream>
#include <type_traits>




class Stack {
public:

	explicit Stack(int capacity = 16) : capacity_(capacity) {
		data_ = new int[capacity_];
		size_ = 0;
	}


	~Stack() {
		delete data_;
		std::cout << "Destructor is running." << std::endl;
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

	//   - Create a stack with small initial capacity (e.g., 4)
	Stack stack = Stack(4);
	//   - Push elements beyond initial capacity — verify it grows
	std::cout << "Capacity: " << stack.capacity() << std::endl;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	stack.print();
	//   - Print size and capacity after each push to see growth
	std::cout << "Capacity: " << stack.capacity() << std::endl;
	//   - Pop elements and print them
	std::cout << "Peek: " << stack.peek() << std::endl;
	std::cout << "Pop: " << stack.pop() << std::endl;
	std::cout << "Pop: " << stack.pop() << std::endl;
	std::cout << "Pop: " << stack.pop() << std::endl;
	stack.print();
	//   - Try popping from empty stack — catch the exception
	std::cout << "Pop: " << stack.pop() << std::endl;
	std::cout << "Pop: " << stack.pop() << std::endl;
	//std::cout << "Pop: " << stack.pop() << std::endl;

	//   - Demonstrate RAII: create a stack in a block {}, verify destructor runs

	
	{
		Stack stack1 = Stack(10);
	}
	


}
