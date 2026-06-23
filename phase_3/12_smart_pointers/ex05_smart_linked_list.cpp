// Exercise 5: Smart Pointer Linked List
//
// Task: Rebuild the singly linked list from step 05 using smart pointers.
//       Compare how much simpler memory management becomes.
//
// Define:
//
//   struct Node {
//       int data;
//       std::unique_ptr<Node> next;
//
//       Node(int val) : data(val), next(nullptr) {}
//       ~Node() { std::cout << "Node " << data << " destroyed\n"; }
//   };
//
//   class LinkedList {
//   public:
//       LinkedList() = default;
//
//       // Rule of Five: unique_ptr is move-only, so the list is move-only
//       LinkedList(const LinkedList&) = delete;
//       LinkedList& operator=(const LinkedList&) = delete;
//       LinkedList(LinkedList&&) = default;
//       LinkedList& operator=(LinkedList&&) = default;
//
//       void push_front(int value);
//       void push_back(int value);
//       void pop_front();
//       bool contains(int value) const;
//       int size() const;
//       bool empty() const;
//       void print() const;
//       void clear();
//
//       // Note: remove is trickier with unique_ptr than raw pointers.
//       // You need to walk with raw pointer references:
//       void remove(int value);
//
//   private:
//       std::unique_ptr<Node> head_;
//   };
//
// Implementation hints:
//
//   push_front:
//     auto new_node = std::make_unique<Node>(value);
//     new_node->next = std::move(head_);   // new node takes ownership of old head
//     head_ = std::move(new_node);         // head now points to new node
//
//   push_back:
//     if (!head_) { push_front(value); return; }
//     Node* cur = head_.get();          // .get() returns raw pointer for traversal
//     while (cur->next) cur = cur->next.get();
//     cur->next = std::make_unique<Node>(value);
//
//   pop_front:
//     head_ = std::move(head_->next);   // old head is automatically deleted!
//
//   remove:
//     // Need to find the node BEFORE the target so you can reassign its next
//     // Use raw pointers for traversal, unique_ptr for ownership changes
//
//   clear:
//     head_.reset();   // or head_ = nullptr;
//     // This triggers a chain: head_ deleted → its next deleted → etc.
//     // WARNING: for very long lists this can cause stack overflow from
//     // recursive destructor calls. For this exercise it's fine.
//
// In main():
//   - Build a list: push_back 1, 2, 3, 4, 5
//   - Print it
//   - push_front 0, print
//   - Remove 3, print
//   - pop_front, print
//   - contains(2)? contains(99)?
//   - clear, print (should be empty)
//   - Observe: NO delete anywhere in your code!
//
// Compare to your step 05 linked list:
//   - No delete[] or delete
//   - No clear() walking the list and deleting each node
//   - No memory leaks possible
//   - Less code, safer code
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_smart_linked_list.cpp

// YOUR CODE HERE
