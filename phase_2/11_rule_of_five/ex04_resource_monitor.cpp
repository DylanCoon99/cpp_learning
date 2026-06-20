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
