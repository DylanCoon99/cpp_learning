# Step 08: Classes

## Concepts

You already used structs with methods in step 07. A `class` in C++ is essentially the same thing, but with **private access by default**. This step covers the full class toolkit: encapsulation, constructors, destructors, and RAII.

### 1. Class vs. Struct

```cpp
struct Foo {
    int x;          // public by default
};

class Bar {
    int x;          // private by default
public:
    int get_x() const { return x; }
};
```

**Convention:** Use `struct` for plain data (all public, no invariants to protect). Use `class` when you have private state, constructors that enforce invariants, or non-trivial behavior.

### 2. Access Specifiers

```cpp
class Account {
public:     // accessible from anywhere
    std::string name;
    void deposit(double amount);

protected:  // accessible from this class and subclasses
    double interest_rate;

private:    // accessible only from this class
    double balance;
    void apply_fee();
};
```

- `public` — the interface: what users of your class call
- `private` — implementation details: internal state and helpers
- `protected` — we'll use this more in step 10 (inheritance)

**Encapsulation:** Hide your data, expose behavior. Users of the class shouldn't depend on how it stores things internally.

### 3. Constructors In Depth

```cpp
class BankAccount {
public:
    // Default constructor
    BankAccount() : owner_("unknown"), balance_(0.0) {}

    // Parameterized constructor
    BankAccount(const std::string& owner, double initial_balance)
        : owner_(owner), balance_(initial_balance) {}

    // Delegating constructor (C++11) — calls another constructor
    BankAccount(const std::string& owner)
        : BankAccount(owner, 0.0) {}  // delegates to the two-arg version

private:
    std::string owner_;
    double balance_;
};
```

**Naming convention:** Private members often have a trailing underscore (`balance_`) or prefix (`m_balance`). This avoids name collisions with parameters and makes it clear what's a member. We'll use the trailing underscore convention.

### 4. `explicit` Constructors

```cpp
class Celsius {
public:
    Celsius(double temp) : temp_(temp) {}  // implicit conversion allowed
private:
    double temp_;
};

Celsius c = 36.6;   // compiles! implicit conversion from double to Celsius
                     // This is often a bug — you didn't mean to create a Celsius

class Fahrenheit {
public:
    explicit Fahrenheit(double temp) : temp_(temp) {}
private:
    double temp_;
};

Fahrenheit f = 98.6;          // ERROR: implicit conversion blocked
Fahrenheit f(98.6);           // OK: explicit construction
Fahrenheit f{98.6};           // OK: direct initialization
```

**Rule:** Mark single-argument constructors `explicit` unless you intentionally want implicit conversion. This prevents subtle bugs.

### 5. Destructors

A destructor runs when an object is destroyed (goes out of scope, is deleted, etc.). This is where you clean up resources.

```cpp
class FileLogger {
public:
    FileLogger(const std::string& filename)
        : file_(std::fopen(filename.c_str(), "w")) {
        if (!file_) throw std::runtime_error("Cannot open file");
    }

    ~FileLogger() {
        if (file_) {
            std::fclose(file_);   // clean up the resource
            std::cout << "File closed.\n";
        }
    }

    void log(const std::string& message) {
        std::fprintf(file_, "%s\n", message.c_str());
    }

private:
    FILE* file_;
};

{
    FileLogger logger("app.log");
    logger.log("started");
    logger.log("running");
}   // logger goes out of scope here — destructor runs, file is closed
```

### 6. RAII — Resource Acquisition Is Initialization

The most important C++ idiom. The idea:
- **Acquire** a resource (memory, file, lock, connection) in the **constructor**
- **Release** it in the **destructor**
- Because destructors run automatically when objects go out of scope, resources are always cleaned up — even if exceptions occur

```cpp
// RAII wrapper for a dynamic array
class IntArray {
public:
    explicit IntArray(int size)
        : size_(size), data_(new int[size]{}) {}   // acquire

    ~IntArray() {
        delete[] data_;                              // release
    }

    int size() const { return size_; }
    int& operator[](int i) { return data_[i]; }
    const int& operator[](int i) const { return data_[i]; }

private:
    int size_;
    int* data_;
};

void example() {
    IntArray arr(10);   // memory allocated
    arr[0] = 42;
    // ... use arr ...
}   // arr destroyed — memory automatically freed, no leak possible
```

Compare this to C where you'd write `int* arr = malloc(...)` and hope you remember to `free(arr)` on every exit path. RAII makes resource leaks structurally impossible.

### 7. Getters and Setters

```cpp
class Temperature {
public:
    explicit Temperature(double celsius) : celsius_(celsius) {}

    // Getter
    double celsius() const { return celsius_; }
    double fahrenheit() const { return celsius_ * 9.0 / 5.0 + 32.0; }

    // Setter with validation
    void set_celsius(double c) {
        if (c < -273.15) {
            throw std::invalid_argument("Below absolute zero");
        }
        celsius_ = c;
    }

private:
    double celsius_;
};
```

Don't blindly add getters/setters for every field — that defeats the purpose of encapsulation. Only expose what users of the class actually need.

### 8. `this` Pointer

Inside a method, `this` is a pointer to the current object:

```cpp
class Counter {
public:
    // 'this' is implicit — you rarely need to write it
    void increment() { count_++; }       // same as this->count_++

    // Useful for chaining (returning *this):
    Counter& add(int n) {
        count_ += n;
        return *this;   // return reference to self
    }

private:
    int count_ = 0;
};

Counter c;
c.add(5).add(3).add(1);  // method chaining — each call returns *this
```

### 9. `= default` and `= delete`

```cpp
class Widget {
public:
    Widget() = default;           // compiler generates default constructor
    Widget(const Widget&) = delete;  // NO copying allowed
    Widget& operator=(const Widget&) = delete;  // NO copy assignment
};

Widget a;
Widget b = a;   // ERROR: copy constructor is deleted
```

`= delete` is how you explicitly forbid operations. Useful when copying doesn't make sense (e.g., a file handle, a thread, a unique resource).

### 10. `static` Members in Classes

```cpp
class Player {
public:
    Player(const std::string& name) : name_(name), id_(next_id_++) {}

    static int player_count() { return next_id_; }

private:
    std::string name_;
    int id_;
    static int next_id_;  // shared across all instances
};

int Player::next_id_ = 0;  // define outside the class
```

You already used this pattern with `Contact::count` in your project — same idea, now with proper class syntax.

---

## Exercises

1. **ex01_bank_account.cpp** — Class with encapsulation, validation, method chaining
2. **ex02_string_class.cpp** — Build a simplified string class with RAII
3. **ex03_date_class.cpp** — Date class with validation and comparison
4. **ex04_stack.cpp** — RAII stack (dynamic array under the hood)
5. **ex05_game_entity.cpp** — Refactor the ECS from step 07 into proper classes
