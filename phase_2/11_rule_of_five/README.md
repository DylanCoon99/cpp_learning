# Step 11: The Rule of Five

## Concepts

### 1. The Problem

In step 08 you wrote classes like `MyString` and `Stack` that manage raw resources (heap memory). You wrote constructors and destructors. But what happens when you **copy** or **move** these objects?

```cpp
MyString a("hello");
MyString b = a;       // copy — what happens?
```

The compiler generates a default copy constructor that copies each member. For `data_` (a raw pointer), it copies the **pointer value** — now `a` and `b` point to the same memory. When both are destroyed, they both `delete[]` the same memory → **double free → crash**.

This is the problem the Rule of Five solves.

### 2. The Five Special Member Functions

If your class manages a resource, you must define (or delete) all five:

```
1. Destructor             ~T()
2. Copy constructor       T(const T& other)
3. Copy assignment        T& operator=(const T& other)
4. Move constructor       T(T&& other)
5. Move assignment        T& operator=(T&& other)
```

If you define any one of these, you should define all five.

### 3. Copy Constructor

Creates a new object as a **deep copy** of another:

```cpp
class IntArray {
public:
    IntArray(int size) : size_(size), data_(new int[size]{}) {}

    // Copy constructor — deep copy
    IntArray(const IntArray& other)
        : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    ~IntArray() { delete[] data_; }

private:
    int size_;
    int* data_;
};

IntArray a(5);
IntArray b = a;   // calls copy constructor — b has its OWN copy of the data
```

### 4. Copy Assignment Operator

Assigns an existing object from another. Must handle self-assignment and clean up old resources:

```cpp
IntArray& operator=(const IntArray& other) {
    if (this == &other) return *this;   // self-assignment check

    delete[] data_;                      // free old resource

    size_ = other.size_;
    data_ = new int[size_];
    std::copy(other.data_, other.data_ + size_, data_);

    return *this;
}
```

**Copy-and-swap idiom** — a cleaner, exception-safe approach:

```cpp
// Requires a swap function:
void swap(IntArray& other) noexcept {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

// Copy assignment using copy-and-swap:
IntArray& operator=(IntArray other) {   // note: takes by VALUE (makes a copy)
    swap(other);                         // swap our guts with the copy
    return *this;                        // old data destroyed when 'other' goes out of scope
}
```

This approach is:
- Self-assignment safe (swapping with yourself is fine)
- Exception safe (if the copy fails, we haven't modified `this`)
- Simple (reuses the copy constructor)

### 5. Rvalue References and Move Semantics

An **rvalue** is a temporary — something that's about to be destroyed:

```cpp
std::string getName() { return "Dylan"; }

std::string a = getName();   // the returned string is a temporary (rvalue)
                              // why copy it when we can STEAL its guts?
```

**Rvalue references** (`T&&`) bind to temporaries:

```cpp
int& ref = 42;       // ERROR: can't bind lvalue ref to rvalue
int&& rref = 42;     // OK: rvalue reference

std::string&& s = getName();   // binds to the temporary
```

### 6. Move Constructor

"Steals" the resources from a temporary instead of copying:

```cpp
// Move constructor — steal resources from a dying object
IntArray(IntArray&& other) noexcept
    : size_(other.size_), data_(other.data_) {
    // Steal the pointer
    other.data_ = nullptr;   // leave source in a valid but empty state
    other.size_ = 0;
}
```

After a move, the source object must be in a **valid but unspecified state** — safe to destroy, but don't use its data.

### 7. Move Assignment Operator

```cpp
IntArray& operator=(IntArray&& other) noexcept {
    if (this == &other) return *this;

    delete[] data_;          // free our old resource

    data_ = other.data_;    // steal
    size_ = other.size_;

    other.data_ = nullptr;  // leave source valid
    other.size_ = 0;

    return *this;
}
```

Or using swap:

```cpp
IntArray& operator=(IntArray&& other) noexcept {
    swap(other);    // swap guts — other will clean up our old data when destroyed
    return *this;
}
```

### 8. `std::move`

`std::move` doesn't actually move anything — it **casts** an lvalue to an rvalue reference, enabling the move constructor/assignment to be called:

```cpp
IntArray a(10);
IntArray b = std::move(a);   // calls MOVE constructor
                              // a is now in a valid but empty state
                              // DO NOT use a's data after this
```

Without `std::move`, `b = a` would call the copy constructor because `a` is an lvalue.

### 9. `noexcept`

Move operations should be marked `noexcept`. This is important because:
- `std::vector` will only use move (instead of copy) during reallocation if the move constructor is `noexcept`
- If a move can throw, the vector can't safely roll back on failure

```cpp
IntArray(IntArray&& other) noexcept;              // promise: won't throw
IntArray& operator=(IntArray&& other) noexcept;   // promise: won't throw
```

### 10. The Rule of Zero

If your class doesn't manage raw resources directly, you don't need ANY of the five. Let the compiler generate them:

```cpp
class Student {
    std::string name;      // manages its own memory
    std::vector<int> grades;  // manages its own memory
    int age;
};

// No destructor, no copy/move constructors, no assignment operators needed.
// The compiler-generated versions do the right thing because all members
// handle their own resources.
```

**Rule of Zero:** Prefer classes that don't need custom resource management. Use `std::string`, `std::vector`, smart pointers, etc. — they handle it for you.

**Rule of Five:** If you DO manage a raw resource, define all five.

### 11. When Each Gets Called

```cpp
IntArray a(10);              // constructor
IntArray b = a;              // copy constructor
IntArray c(a);               // copy constructor (same thing)
IntArray d = std::move(a);   // move constructor
b = c;                       // copy assignment
c = std::move(d);            // move assignment
// destructor called for each when they go out of scope
```

### 12. Complete Example

```cpp
class Buffer {
public:
    explicit Buffer(int size)
        : size_(size), data_(new int[size]{}) {}

    // Destructor
    ~Buffer() { delete[] data_; }

    // Copy constructor
    Buffer(const Buffer& other)
        : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // Copy assignment (copy-and-swap)
    Buffer& operator=(Buffer other) {
        swap(other);
        return *this;
    }

    // Move constructor
    Buffer(Buffer&& other) noexcept
        : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
    }

    // Move assignment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    void swap(Buffer& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

private:
    int size_;
    int* data_;
};
```

---

## Exercises

1. **ex01_deep_copy.cpp** — Add copy semantics to MyString from step 08
2. **ex02_move_semantics.cpp** — Add move semantics to MyString
3. **ex03_rule_of_five_stack.cpp** — Complete Rule of Five for the Stack from step 08
4. **ex04_resource_monitor.cpp** — Build a class that logs every special member function call
5. **ex05_dynamic_array.cpp** — Build a complete DynamicArray template (preview of templates)
