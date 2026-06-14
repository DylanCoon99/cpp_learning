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
#include<iostream>



struct Node {
	int data;
	Node* next;
};



void push_front(Node*& head, int value) {

	// create a new node
	Node* n = new Node{value, nullptr};

	n->next = head;
	head = n;

}


void push_back(Node*& head, int value) {
	Node* n = new Node{value, nullptr};

	if (head == nullptr) {
		head = n;
		return;
	}

	Node* cur = head;

	while (cur->next) {
		cur = cur->next;
	}

	cur->next = n;
}


void print_list(const Node* head) {

	if (head == nullptr) {
		return;
	}
	
	const Node* cur = head; // non const ptr to a const Node

	while (cur) {
		std::cout << cur->data << "->";
		cur = cur->next;
	}


	std::cout << "null" << std::endl;

}

int size(const Node* head) {

	int size = 0;
	const Node* cur = head;

	while (cur) {
		size++;
		cur = cur->next;
	}

	return size;
}


bool contains(const Node* head, int value) {

	if (head == nullptr) {
		return false;
	}


	const Node* cur = head;

	while (cur) {
		if (cur->data == value) {
			return true;
		}
		cur = cur->next;
	}

	return false;

}


void remove_first(Node*& head, int value) {

	if (head == nullptr) {
		return;
	}

	Node* cur = head;
	Node* cur_next = cur->next;

	while (true) {
		if (cur->data == value) {
			head = cur_next;
			cur->next = nullptr;
			delete cur;
			break;
		}
		if (cur_next) {
			if (cur_next->data == value) {
				// delete the next node
				cur->next = cur_next->next;
				delete cur_next;
				break;
			}
		}
		else {
			break;
		}

		cur = cur_next;
		cur_next = cur_next->next;
	}

}

void clear(Node*& head) {

	if (head == nullptr) {
		return;
	}

	Node* cur = head;
	Node* temp;

	while (cur->next) {
		temp = cur->next;
		delete cur;
		cur = temp;
	}


	head = nullptr;

}


int main() {

	Node* head = nullptr;

	push_back(head, 1);
	print_list(head);
	push_back(head, 2);
	print_list(head);
	push_back(head, 3);
	print_list(head);
	push_back(head, 4);
	print_list(head);
	push_back(head, 5);
	print_list(head);



	
	push_front(head, 0);
	print_list(head);
	std::cout << "Size: " << size(head) << std::endl;

	
	remove_first(head, 3);
	print_list(head);

	remove_first(head, 0);
	print_list(head);
	
	std::cout << "contains 0: " << (contains(head, 0) ? "true" : "false") << std::endl;	
	std::cout << "contains 5: " << (contains(head, 5) ? "true" : "false") << std::endl;

	clear(head);
	print_list(head);
	


}


