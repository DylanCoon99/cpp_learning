// Exercise 2: Class Templates
//
// Task: Build generic data structures using class templates.
//
// Part A — Generic Pair:
//
//   template <typename T, typename U>
//   class Pair {
//   public:
//       Pair(const T& first, const U& second);
//       T& first();
//       U& second();
//       const T& first() const;
//       const U& second() const;
//
//       void print() const;  // prints "(first, second)"
//
//       // Comparison (compares first, then second if firsts are equal)
//       bool operator==(const Pair& other) const;
//       bool operator<(const Pair& other) const;
//
//       friend std::ostream& operator<<(std::ostream& os, const Pair& p);
//
//   private:
//       T first_;
//       U second_;
//   };
//
//   Test with:
//     Pair<int, std::string> p1(1, "hello");
//     Pair<double, double> p2(3.14, 2.71);
//     Pair<std::string, int> p3("age", 25);
//
//   This is a simplified version of std::pair.
//
// Part B — Generic Stack:
//
//   template <typename T>
//   class Stack {
//   public:
//       void push(const T& value);
//       T pop();
//       const T& top() const;
//       bool empty() const;
//       int size() const;
//
//       friend std::ostream& operator<<(std::ostream& os, const Stack& s);
//
//   private:
//       std::vector<T> data_;
//   };
//
//   Test with:
//     Stack<int> — push ints, pop them
//     Stack<std::string> — push strings
//     Stack<Pair<int, int>> — stack of pairs (templates of templates!)
//
// Part C — Generic with non-type parameter:
//
//   template <typename T, int Capacity>
//   class FixedStack {
//   public:
//       void push(const T& value);  // throw if full
//       T pop();                     // throw if empty
//       bool full() const;
//       bool empty() const;
//       int size() const;
//   private:
//       T data_[Capacity];   // stack-allocated, no heap!
//       int size_ = 0;
//   };
//
//   Test with:
//     FixedStack<int, 5> — push 5 elements, try pushing 6th (should throw)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_class_template.cpp

// YOUR CODE HERE
#include <iostream>
#include <stdexcept>
#include <string>


template <typename T, typename U>
class Pair {
public:
	Pair(const T& first, const U& second) : first_(first), second_(second) {};

	T& first()  {
		return first_;
	}

	U& second() {
		return second_;
	}

	const T& first() const {
		return first_;
	}
	const U& second() const {
		return second_;
	}

	void print() const {
		// prints "(first, second)"
		std::cout << "(" << first_ << ", " << second_ << std::cout; 
	}

	// Comparison (compares first, then second if firsts are equal)
	bool operator==(const Pair& other) const {
		return (first_ == other.first_) && (second_ == other.second_);
	}
	bool operator<(const Pair& other) const {
		return (first_ < other.first_) && (second_ < other.second_);
	}

friend std::ostream& operator<<(std::ostream& os, const Pair& p) {

	os << p.first_ << " " << p.second_;

	return os;
}

private:
	T first_;
	U second_;
};


// Part B
template <typename T>
class Stack {

public:

	Stack() = default;

	void push(const T& value) {
		data_.push_back(value);
	}

	T pop() {
		T top = data_.back();                   
		data_.pop_back();                                                                                                                                                              
		return top; 
	}

	const T& top() const {
		return data_.back();
	}

	bool empty() const {
		return data_.size() == 0;
	}

	int size() const {
		return data_.size();
	}

	friend std::ostream& operator<<(std::ostream& os, const Stack& s) {
		for (auto& e : s) {
			os << e << " ";
		}
		os << std::endl;
		return os;
	}

private:
	std::vector<T> data_;
};


// Part C
template <typename T, int Capacity>
class FixedStack {

public:
	void push(const T& value) {
		if (full()) {
			// throw if full
			throw std::runtime_error("The stack is full!");
		}
		data_[size_] = value;
		++size_;
	}

	T pop() {
		// throw if empty
		if (empty()) {
			throw std::runtime_error("The stack is empty!");
		}
		T ret = data_[size_ - 1];
		--size_;
		return ret;
	}
	
	bool full() const {
		return Capacity == size_;
	}

	bool empty() const {
		return size_ == 0;
	}

	int size() const {
		return size_;
	}

private:
	T data_[Capacity];   // stack-allocated, no heap!
	int size_ = 0;
};



int main() {

	// Part A Test
	{
		Pair<int, std::string> p1(1, "hello");
		Pair<double, double> p2(3.14, 2.71);
		Pair<std::string, int> p3("age", 25);

		std::cout << "p1: " << p1 << std::endl;
		std::cout << "p2: " << p2 << std::endl;
		std::cout << "p3: " << p3 << std::endl;

		std::cout << "p1.first(): " << p1.first() << std::endl;
		std::cout << "p1.second(): " << p1.second() << std::endl;

		p1.first() = 42;
		p1.second() = "world";
		std::cout << "p1 after modify: " << p1 << std::endl;

		Pair<int, int> a(1, 2);
		Pair<int, int> b(1, 2);
		Pair<int, int> c(1, 3);
		Pair<int, int> d(2, 1);

		std::cout << "a == b: " << (a == b ? "true" : "false") << std::endl;
		std::cout << "a == c: " << (a == c ? "true" : "false") << std::endl;
		std::cout << "a < c: " << (a < c ? "true" : "false") << std::endl;
		std::cout << "a < d: " << (a < d ? "true" : "false") << std::endl;
		std::cout << "d < a: " << (d < a ? "true" : "false") << std::endl;
	}



	// Part B Test
	{
		Stack<int> int_stack;
		int_stack.push(10);
		int_stack.push(20);
		int_stack.push(30);
		std::cout << "int stack size: " << int_stack.size() << std::endl;
		std::cout << "int stack top: " << int_stack.top() << std::endl;
		std::cout << "popped: " << int_stack.pop() << std::endl;
		std::cout << "int stack size after pop: " << int_stack.size() << std::endl;

		Stack<std::string> str_stack;
		str_stack.push("hello");
		str_stack.push("world");
		std::cout << "str stack top: " << str_stack.top() << std::endl;
		std::cout << "str stack empty: " << (str_stack.empty() ? "true" : "false") << std::endl;

		// Stack of Pairs
		Stack<Pair<int, int>> pair_stack;
		pair_stack.push(Pair<int, int>(1, 2));
		pair_stack.push(Pair<int, int>(3, 4));
		std::cout << "pair stack top: " << pair_stack.top() << std::endl;
		std::cout << "pair stack size: " << pair_stack.size() << std::endl;
	}

	// Part C Test
	{
		FixedStack<int, 5> stack;
		stack.push(0);
		stack.push(1);
		stack.push(2);
		stack.push(3);
		stack.push(4);
		stack.push(5);
	}

}