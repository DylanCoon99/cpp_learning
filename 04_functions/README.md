# Step 04: Functions

## Concepts

### 1. Function Basics

Same structure as C, but with some C++ enhancements:

```cpp
// Declaration (prototype) — can go in a header or before main
int add(int a, int b);

// Definition
int add(int a, int b) {
    return a + b;
}
```

Unlike Go, C++ requires functions to be declared before use (or defined above the call site). This is the same as C.

### 2. Function Overloading

C++ allows multiple functions with the same name but different parameter types or counts. This does NOT exist in C or Go.

```cpp
int    add(int a, int b)       { return a + b; }
double add(double a, double b) { return a + b; }
int    add(int a, int b, int c){ return a + b + c; }

add(1, 2);       // calls int version
add(1.5, 2.5);   // calls double version
add(1, 2, 3);    // calls three-arg version
```

The compiler picks the right overload based on the argument types/count. This is called **overload resolution**.

**Ambiguity warning:**
```cpp
void print(int x);
void print(double x);

print(3.14f);  // float — which one? Compiler may warn or error about ambiguity
```

### 3. Default Arguments

Parameters can have default values. C and Go don't have this.

```cpp
void greet(const std::string& name, const std::string& greeting = "Hello") {
    std::cout << greeting << ", " << name << "!\n";
}

greet("Dylan");           // "Hello, Dylan!"
greet("Dylan", "Hey");    // "Hey, Dylan!"
```

Rules:
- Defaults must go right-to-left (no gaps):
  ```cpp
  void f(int a, int b = 5, int c = 10);  // OK
  void f(int a, int b = 5, int c);        // ERROR
  ```
- Defaults go in the **declaration** (prototype), not the definition, when they're separate

### 4. Pass by Value vs. Reference

This is a critical C++ concept. In C you pass by value or by pointer. C++ adds **references**:

```cpp
// Pass by value — copies the argument (same as C)
void modify_val(int x) {
    x = 100;  // only modifies local copy
}

// Pass by reference — operates on the original (no pointer syntax needed)
void modify_ref(int& x) {
    x = 100;  // modifies the original
}

// Pass by const reference — read-only access, no copy
void print_vec(const std::vector<int>& v) {
    for (const auto& n : v) std::cout << n << " ";
}

int a = 42;
modify_val(a);   // a is still 42
modify_ref(a);   // a is now 100
```

**When to use what:**
| Type | When |
|------|------|
| `int x` (by value) | Cheap types: int, double, char, bool, pointers |
| `const T&` (const ref) | Expensive types you only read: string, vector, any class |
| `T&` (ref) | When you need to modify the caller's variable |

This is similar in spirit to Go's pointer receivers, but the syntax is cleaner — no `*` and `&` at every call site.

### 5. `auto` Return Types

```cpp
// Compiler deduces the return type
auto multiply(int a, int b) {
    return a * b;  // returns int
}

// Trailing return type (useful with templates later)
auto divide(double a, double b) -> double {
    return a / b;
}
```

### 6. `inline` Functions

```cpp
inline int square(int x) { return x * x; }
```

`inline` is a *hint* to the compiler to substitute the function body at the call site (avoiding function call overhead). Modern compilers mostly ignore the hint and inline automatically when beneficial. You'll see it in headers to avoid multiple-definition linker errors.

### 7. Forward Declarations

```cpp
// Declare first (forward declaration)
int factorial(int n);

int main() {
    std::cout << factorial(5) << "\n";  // works — declared above
}

// Define later
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

### 8. `[[nodiscard]]`

A C++17 attribute that warns if the caller ignores the return value:

```cpp
[[nodiscard]] int compute() { return 42; }

compute();          // WARNING: ignoring return value
int x = compute();  // OK
```

Useful for error codes or functions where ignoring the result is almost certainly a bug.

---

## Exercises

1. **ex01_overloads.cpp** — Write overloaded functions
2. **ex02_defaults.cpp** — Functions with default arguments
3. **ex03_pass_by.cpp** — Demonstrate value vs. reference vs. const reference
4. **ex04_recursion.cpp** — Recursive functions
5. **ex05_higher_order.cpp** — Functions that take/return function pointers
