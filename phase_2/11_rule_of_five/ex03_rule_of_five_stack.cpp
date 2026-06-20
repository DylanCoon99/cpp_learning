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
