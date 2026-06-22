// Exercise 4: Resource Monitor — Observe Every Special Member Function
//
// Task: Build a class that prints a message every time a special member
//       function is called. This helps you understand WHEN each gets invoked.
//
// Class definition:
//
//   class Resource {
//   public:
//       explicit Resource(const std::string& name);
//       ~Resource();
//       Resource(const Resource& other);
//       Resource& operator=(const Resource& other);
//       Resource(Resource&& other) noexcept;
//       Resource& operator=(Resource&& other) noexcept;
//
//   private:
//       std::string name_;
//       int* data_;        // dummy resource to make moves meaningful
//       static int count_; // track total alive instances
//   };
//
// Each function should print what's happening:
//   Resource("test")              → "Resource 'test' CONSTRUCTED (alive: 1)"
//   ~Resource()                   → "Resource 'test' DESTROYED (alive: 0)"
//   Resource(const Resource&)     → "Resource 'test' COPY CONSTRUCTED (alive: 2)"
//   operator=(const Resource&)    → "Resource 'test' COPY ASSIGNED from 'other'"
//   Resource(Resource&&)          → "Resource 'test' MOVE CONSTRUCTED (alive: 2)"
//   operator=(Resource&&)         → "Resource 'test' MOVE ASSIGNED from 'other'"
//
// In main(), run these scenarios and observe the output:
//
//   1. Basic lifecycle:
//      { Resource r("A"); }  // construct + destroy
//
//   2. Copy:
//      Resource a("B");
//      Resource b = a;        // which function?
//      Resource c("C");
//      c = a;                 // which function?
//
//   3. Move:
//      Resource d = std::move(a);   // which function?
//      Resource e("E");
//      e = std::move(d);            // which function?
//
//   4. Function return:
//      auto make = []() { return Resource("F"); };
//      Resource f = make();    // copy, move, or elided?
//
//   5. Vector operations:
//      std::vector<Resource> v;
//      v.push_back(Resource("G"));   // what gets called?
//      v.push_back(Resource("H"));   // does G get moved/copied when vector grows?
//      v.reserve(10);
//      v.push_back(Resource("I"));   // what about now?
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_resource_monitor.cpp

// YOUR CODE HERE
#include <string>
#include <iostream>


class Resource {
public:
	explicit Resource(const std::string& name) : name_(name), data_(new int[size_ = 5]{}) {
		// "Resource 'test' CONSTRUCTED (alive: 1)
		++count_;
		std::cout << "Resource " << "'" << name_ << "' CONSTRUCTED (alive: " << count_ << ")" << std::endl;
	}

	~Resource() {
		delete[] data_;
		--count_;
		std::cout << "Resource " << "'" << name_ << "' DESTROYED (alive: " << count_ << ")" << std::endl;
	}

	Resource(const Resource& other) : name_(other.name_), data_(new int[size_ = 5]{}) {
		// deep copy constructor
		++count_;
		std::cout << "Resource " << "'" << name_ << "' COPY CONSTRUCTED (alive: " << count_ << ")" << std::endl;
		std::copy(other.data_, other.data_ + other.size_, data_);
	}

	Resource& operator=(const Resource& other) {
		// copy assignment
		std::cout << "Resource " << "'" << name_ << "' COPY ASSIGNED from '" << other.name_ << "'" << std::endl;
		if (this == &other) return *this;

		delete[] data_;
		data_ = new int[size_];
		name_ = other.name_;
		std::copy(other.data_, other.data_ + other.size_, data_);
		return *this;
	}

	Resource(Resource&& other) noexcept {
		// move constructor
		++count_;
		std::cout << "Resource " << "'" << name_ << "' MOVE CONSTRUCTED (alive: " << count_ << ")" << std::endl;
		data_ = new int[size_];
		name_ = other.name_;
		std::copy(other.data_, other.data_ + other.size_, data_);


		delete[] other.data_;

		other.data_ = nullptr;
		other.name_ = "";

	}
	Resource& operator=(Resource&& other) noexcept {
		// move assignment
		std::cout << "Resource " << "'" << name_ << "' MOVE ASSIGNED from '" << other.name_ << "'" << std::endl;
		if (this == &other) return *this;

		delete[] data_;

		data_ = new int[size_];
		name_ = other.name_;
		std::copy(other.data_, other.data_ + other.size_, data_);


		delete[] other.data_;

		other.data_ = nullptr;
		other.name_ = "";

		return *this;
	}
private:
	std::string name_;
	int* data_;        // dummy resource to make moves meaningful
	int size_ = 5;
	static int count_; // track total alive instances
};



// initialize static variable
int Resource::count_ = 0;



int main() {

	//   1. Basic lifecycle:
	//      { Resource r("A"); }  // construct + destroy
	std::cout << "1. Basic lifecycle:" << std::endl;
	{
		Resource r("A");
	}
	
	std::cout << std::endl;
	std::cout << "2. Copy:" << std::endl;
	//   2. Copy:
	//      Resource a("B");
	//      Resource b = a;        // which function?
	//      Resource c("C");
	//      c = a;                 // which function?
	
	
	Resource a("B");
	Resource b = a;   // this should be copy constructor
	Resource c("C");
	c = a;            // this should be copy assignment
	

	std::cout << std::endl;
	std::cout << "3. Move:" << std::endl;
	//   3. Move:
	//      Resource d = std::move(a);   // which function?
	//      Resource e("E");
	//      e = std::move(d);            // which function?
	
	Resource d = std::move(a); // move constructor
	Resource e("E");
	e = std::move(d); // move assignment


	std::cout << std::endl;
	std::cout << "4. Function return:" << std::endl;
	//   4. Function return:
	//      auto make = []() { return Resource("F"); };
	//      Resource f = make();    // copy, move, or elided?
	auto make = []() { return Resource("F"); };
	Resource f = make();

	std::cout << std::endl;
	std::cout << "5. Vector operations:" << std::endl;
	//   5. Vector operations:
	//      std::vector<Resource> v;
	//      v.push_back(Resource("G"));   // what gets called?
	//      v.push_back(Resource("H"));   // does G get moved/copied when vector grows?
	//      v.reserve(10);
	//      v.push_back(Resource("I"));   // what about now?
	std::vector<Resource> v;
	v.push_back(Resource("G"));
	v.push_back(Resource("H"));
	v.reserve(10);
	v.push_back(Resource("I"));



}

