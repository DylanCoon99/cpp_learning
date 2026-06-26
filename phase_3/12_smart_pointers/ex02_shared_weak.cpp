// Exercise 2: shared_ptr and weak_ptr
//
// Task: Understand shared ownership and the circular reference problem.
//
// Part A — shared_ptr basics:
//   - Create a shared_ptr<int> with make_shared
//   - Copy it to two more shared_ptrs
//   - After each copy, print use_count()
//   - Destroy copies in a block {}, print use_count after each step
//   - Reset the original, observe the final delete
//
// Part B — Circular reference problem:
//   Define:
//     struct BadNode {
//         std::string name;
//         std::shared_ptr<BadNode> partner;
//         ~BadNode() { std::cout << name << " destroyed\n"; }
//     };
//
//   - Create two BadNodes that point to each other:
//       auto a = std::make_shared<BadNode>("A");
//       auto b = std::make_shared<BadNode>("B");
//       a->partner = b;
//       b->partner = a;
//   - Let a and b go out of scope
//   - Observe: NEITHER destructor prints. Memory is leaked!
//   - Add a comment explaining why (circular ref count never reaches 0)
//
// Part C — Fix with weak_ptr:
//   Define:
//     struct GoodNode {
//         std::string name;
//         std::weak_ptr<GoodNode> partner;   // weak — doesn't own
//         ~GoodNode() { std::cout << name << " destroyed\n"; }
//
//         void greet() const {
//             if (auto p = partner.lock()) {
//                 std::cout << name << "'s partner is " << p->name << "\n";
//             } else {
//                 std::cout << name << " has no partner\n";
//             }
//         }
//     };
//
//   - Create two GoodNodes that point to each other via weak_ptr
//   - Call greet() on each
//   - Let them go out of scope — both destructors should run
//   - Verify the leak is fixed
//
// Part D — weak_ptr as a cache:
//   - Create a shared_ptr<std::string>
//   - Create a weak_ptr observing it
//   - Lock the weak_ptr and use the string
//   - Reset the shared_ptr
//   - Try to lock again — should fail (expired)
//   - Print expired() result
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex02 ex02_shared_weak.cpp

// YOUR CODE HERE
#include <iostream>
#include <memory>



struct BadNode {
	std::string name;
	std::shared_ptr<BadNode> partner;
	BadNode(const std::string& n) : name(n) { }
	~BadNode() { std::cout << name << " destroyed\n"; }
};


struct GoodNode {
	std::string name;
	std::weak_ptr<GoodNode> partner;   // weak — doesn't own
	GoodNode(const std::string& n) : name(n) { }
	~GoodNode() { std::cout << name << " destroyed\n"; }

	void greet() const {
		if (auto p = partner.lock()) {
			std::cout << name << "'s partner is " << p->name << "\n";
		} else {
			std::cout << name << " has no partner\n";
		}
	}
};

int main() {

	// Part A
	// shared pointers can have multiple owners
	auto a = std::make_shared<int>(5);  // ref count = 1
	{
	    auto b = a;    // ref count = 2 (copy is OK — increases ref count)
	    auto c = a;    // ref count = 3

	    std::cout << "Count: " << a.use_count() << std::endl;
	}   // b and c destroyed → ref count = 1
	// a still valid, ref count = 1
	std::cout << "Count: " << a.use_count() << std::endl;
	a.reset();  // explicitly release → ref count = 0 → Widget deleted

	// Check ref count
	std::cout << "Count: " << a.use_count() << std::endl;  // number of shared_ptrs sharing this object


	// Part B
	{
		auto x = std::make_shared<BadNode>("X");
		auto y = std::make_shared<BadNode>("Y");
		x->partner = y;
		y->partner = x;
		// To free x we need to free x->partner (y). to free y we need to free y->partner (x). we are stuck
	}

	// Part C
	{
		auto a = std::make_shared<GoodNode>("A");
		auto b = std::make_shared<GoodNode>("B");
		a->partner = b;
		b->partner = a;
	}


	// Part D
	auto my_str = std::make_shared<std::string>("This is my string.");
	std::weak_ptr<std::string> my_weak_ptr = my_str;

	if (auto ptr = my_weak_ptr.lock()) {
		std::cout << "Here is my string: " << *ptr << std::endl;
	} else {
		std::cout << "The str has been deleted!" << std::endl;
	}

	my_str.reset();

	std::cout << "Reference Count: " << my_str.use_count() << std::endl;

	if (auto ptr = my_weak_ptr.lock()) {
		std::cout << "Here is my string: " << *ptr << std::endl;
	} else {
		std::cout << "The str has been deleted!" << std::endl;
	}

}
