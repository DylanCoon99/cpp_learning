# Step 12: Smart Pointers

## Concepts

Throughout Phase 1 and 2 you used `new`/`delete` and raw pointers. You've seen how easy it is to leak memory, double-free, or use dangling pointers. Smart pointers fix all of this by applying RAII to pointer ownership.

### 1. The Problem with Raw Pointers

```cpp
void dangerous() {
    Widget* w = new Widget();
    if (something_fails()) return;  // LEAK: w never deleted
    w->do_work();
    delete w;
}

void also_dangerous() {
    Widget* w = new Widget();
    w->do_work();     // if this throws, delete never runs → LEAK
    delete w;
}
```

Smart pointers wrap raw pointers and automatically `delete` when they go out of scope — RAII applied to heap memory.

### 2. `std::unique_ptr` — Exclusive Ownership

One owner, one pointer. When the `unique_ptr` goes out of scope, the object is deleted. This is the smart pointer you should use **by default**.

```cpp
#include <memory>

// Creating
auto p = std::make_unique<Widget>(constructor_args);  // preferred
std::unique_ptr<Widget> p2(new Widget());              // also works

// Using — same as raw pointer
p->do_work();
(*p).do_work();

// Automatic cleanup
{
    auto w = std::make_unique<Widget>();
    w->do_work();
}   // w goes out of scope → Widget is deleted automatically

// Cannot copy — ownership is exclusive
auto a = std::make_unique<Widget>();
auto b = a;              // ERROR: copy deleted
auto c = std::move(a);   // OK: transfer ownership
// a is now nullptr, c owns the Widget
```

**Key properties:**
- Zero overhead — same size as a raw pointer
- Cannot be copied (deleted copy constructor)
- Can be moved (transfers ownership)
- Automatically deletes when destroyed
- Use `std::make_unique<T>(args)` to create (exception-safe, cleaner)

### 3. `unique_ptr` with Custom Deleters

For resources that aren't freed with `delete`:

```cpp
// FILE* needs fclose, not delete
auto file = std::unique_ptr<FILE, decltype(&fclose)>(
    fopen("data.txt", "r"), fclose
);
// file is automatically fclose'd when it goes out of scope
```

### 4. `std::shared_ptr` — Shared Ownership

Multiple pointers can share ownership. The object is deleted when the **last** `shared_ptr` to it is destroyed. Uses reference counting internally.

```cpp
auto a = std::make_shared<Widget>();  // ref count = 1
{
    auto b = a;    // ref count = 2 (copy is OK — increases ref count)
    auto c = a;    // ref count = 3
    b->do_work();
}   // b and c destroyed → ref count = 1
// a still valid, ref count = 1

a.reset();  // explicitly release → ref count = 0 → Widget deleted

// Check ref count
std::cout << a.use_count();  // number of shared_ptrs sharing this object
```

**Key properties:**
- Overhead: larger than raw pointer (stores ref count + control block)
- Can be copied (increments ref count)
- Can be moved (transfers without changing ref count)
- Thread-safe ref counting (atomic increment/decrement)
- Use `std::make_shared<T>(args)` to create (more efficient — single allocation)

### 5. `std::weak_ptr` — Non-Owning Observer

A `weak_ptr` observes a `shared_ptr` without affecting the ref count. It solves the **circular reference** problem.

```cpp
auto shared = std::make_shared<Widget>();
std::weak_ptr<Widget> weak = shared;   // doesn't increase ref count

// To use, must convert to shared_ptr first (might have been deleted):
if (auto locked = weak.lock()) {
    locked->do_work();   // safe — locked keeps it alive
} else {
    std::cout << "Widget was already deleted\n";
}

// Check if the object still exists:
weak.expired();   // true if the shared_ptr was deleted
```

**The circular reference problem:**
```cpp
struct Node {
    std::shared_ptr<Node> next;     // owns the next node
    std::shared_ptr<Node> prev;     // PROBLEM: circular ownership
    // A→B→A: ref counts never reach 0, memory leaks
};

// Fix:
struct Node {
    std::shared_ptr<Node> next;     // forward links own
    std::weak_ptr<Node> prev;       // backward links observe
};
```

### 6. When to Use What

| Type | Use When |
|------|----------|
| `unique_ptr` | **Default choice.** Single clear owner. |
| `shared_ptr` | Multiple owners need to share lifetime. Rare. |
| `weak_ptr` | Breaking cycles, caches, observer patterns. |
| Raw pointer | Non-owning observation (function params, etc.). Never for ownership. |
| Raw `new`/`delete` | Almost never. Only in low-level code or custom allocators. |

### 7. Smart Pointers and Polymorphism

Smart pointers work seamlessly with inheritance:

```cpp
class Shape { public: virtual ~Shape() = default; virtual void draw() = 0; };
class Circle : public Shape { public: void draw() override { /*...*/ } };

// Base pointer to derived object — works like raw pointers
std::unique_ptr<Shape> s = std::make_unique<Circle>();
s->draw();  // polymorphic call

// Container of polymorphic objects:
std::vector<std::unique_ptr<Shape>> shapes;
shapes.push_back(std::make_unique<Circle>());
shapes.push_back(std::make_unique<Rectangle>(3, 4));

for (const auto& s : shapes) {
    s->draw();   // calls the right virtual function
}
// ALL shapes automatically deleted when vector is destroyed
```

Compare this to your step 10 exercises where you had to manually `delete` every pointer — smart pointers eliminate that entirely.

### 8. Passing Smart Pointers to Functions

```cpp
// Transfer ownership INTO the function:
void take_ownership(std::unique_ptr<Widget> w);
take_ownership(std::move(my_widget));  // caller gives up ownership

// Share ownership:
void share(std::shared_ptr<Widget> w);  // bumps ref count

// Just use the object (no ownership change):
void use(Widget& w);           // preferred — pass by reference
void use(const Widget& w);    // if read-only
void use(Widget* w);           // if nullable

// DON'T pass unique_ptr by reference unless you might reassign it
// DON'T pass shared_ptr if the function doesn't need to share ownership
```

**Rule of thumb:** Pass the raw object (`T&`, `const T&`, `T*`), not the smart pointer, unless the function needs to participate in ownership.

### 9. `make_unique` and `make_shared` vs. `new`

```cpp
// GOOD:
auto p = std::make_unique<Widget>(args);
auto q = std::make_shared<Widget>(args);

// BAD (less safe, less efficient):
std::unique_ptr<Widget> p(new Widget(args));
std::shared_ptr<Widget> q(new Widget(args));
```

`make_unique`/`make_shared` are preferred because:
- Exception safety: no risk of leak if another argument's constructor throws
- `make_shared` does a single allocation (object + control block together)
- Cleaner syntax

### 10. Smart Pointers and Arrays

```cpp
// unique_ptr can manage arrays:
auto arr = std::make_unique<int[]>(10);   // array of 10 ints
arr[3] = 42;   // operator[] works

// But prefer std::vector<int> over unique_ptr<int[]> in most cases
```

---

## Exercises

1. **ex01_unique_basics.cpp** — unique_ptr fundamentals and ownership transfer
2. **ex02_shared_weak.cpp** — shared_ptr, weak_ptr, and circular reference demo
3. **ex03_polymorphic.cpp** — Refactor step 10 shapes to use smart pointers
4. **ex04_resource_manager.cpp** — Build a resource cache with shared_ptr and weak_ptr
5. **ex05_smart_linked_list.cpp** — Rebuild the linked list from step 05 with smart pointers
