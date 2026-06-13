// Exercise 5: Singly Linked List
//
// Task: Build a simple singly linked list from scratch using pointers.
//       This is a classic exercise that ties together structs, pointers,
//       new/delete, and functions with pointer parameters.
//
// Define:
//   struct Node {
//       int data;
//       Node* next;
//   };
//
// Implement these functions:
//
//   void push_front(Node*& head, int value)
//     — Insert a new node at the front of the list
//     — Note: head is a reference to a pointer (Node*&) because we
//       need to modify the caller's head pointer
//
//   void push_back(Node*& head, int value)
//     — Insert a new node at the end of the list
//
//   void print_list(const Node* head)
//     — Print all values: 1 -> 2 -> 3 -> null
//
//   int size(const Node* head)
//     — Return the number of nodes
//
//   bool contains(const Node* head, int value)
//     — Return true if value exists in the list
//
//   void remove_first(Node*& head, int value)
//     — Remove the first node with the given value
//     — Handle: value at head, value in middle, value not found
//
//   void clear(Node*& head)
//     — Delete all nodes and set head to nullptr
//     — This prevents memory leaks
//
// In main():
//   - Build a list: push_back 1, 2, 3, 4, 5
//   - Print it
//   - push_front 0
//   - Print it and its size
//   - Remove 3, print
//   - Remove 0 (head), print
//   - Check contains for an existing and non-existing value
//   - Clear the list
//   - Print (should show: null)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex05 ex05_linked_list.cpp

// YOUR CODE HERE
