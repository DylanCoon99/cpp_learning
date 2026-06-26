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
