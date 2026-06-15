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
