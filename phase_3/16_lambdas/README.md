# Step 16: Lambdas

## Concepts

You've already used lambdas throughout Phase 3 — as comparators in `std::sort`, predicates in `std::find_if`, etc. This step covers them in depth.

### 1. Lambda Syntax

```cpp
[captures](parameters) -> return_type { body }
```

The simplest lambda:
```cpp
auto greet = []() { std::cout << "hello\n"; };
greet();  // "hello"
```

With parameters:
```cpp
auto add = [](int a, int b) { return a + b; };
std::cout << add(3, 4);  // 7
```

The return type is usually deduced. You can specify it explicitly:
```cpp
auto divide = [](int a, int b) -> double { return static_cast<double>(a) / b; };
```

### 2. Captures

Lambdas can access variables from the enclosing scope via **captures**. This is the key feature that distinguishes them from regular functions.

```cpp
int factor = 3;

// Capture by value — copies the variable
auto multiply = [factor](int x) { return x * factor; };
// factor is copied at the point of lambda creation
// changing factor after this doesn't affect the lambda

// Capture by reference — uses the original variable
auto multiply_ref = [&factor](int x) { return x * factor; };
// uses the current value of factor each time it's called

factor = 10;
multiply(5);      // 15 (uses copied value: 3)
multiply_ref(5);  // 50 (uses current value: 10)
```

**Capture modes:**

```cpp
int a = 1, b = 2, c = 3;

[a]        // capture a by value
[&a]       // capture a by reference
[a, &b]    // a by value, b by reference
[=]        // capture ALL used variables by value
[&]        // capture ALL used variables by reference
[=, &a]    // all by value, except a by reference
[&, a]     // all by reference, except a by value
[this]     // capture the this pointer (inside a class method)
```

**Best practice:** Capture explicitly (`[a, &b]`) rather than using `[=]` or `[&]`. It's clearer what the lambda depends on.

### 3. `mutable` Lambdas

By default, a lambda capturing by value can't modify its copies:

```cpp
int count = 0;
auto counter = [count]() {
    ++count;  // ERROR: can't modify captured-by-value variable
};

// Fix with mutable:
auto counter = [count]() mutable {
    ++count;  // OK — modifies the lambda's internal copy
    return count;
};

counter();  // returns 1
counter();  // returns 2
counter();  // returns 3
// original 'count' is still 0
```

`mutable` lets the lambda modify its internal copies. The original variables are unaffected.

### 4. `std::function` — Type-Erased Function Wrapper

Lambdas have unique, unnamed types. You can't declare a variable of "lambda type" directly. `std::function` wraps any callable (lambda, function pointer, functor) into a uniform type:

```cpp
#include <functional>

// std::function<return_type(param_types)>
std::function<int(int, int)> op;

op = [](int a, int b) { return a + b; };
std::cout << op(3, 4);  // 7

op = [](int a, int b) { return a * b; };
std::cout << op(3, 4);  // 12

// Works with regular functions too:
int subtract(int a, int b) { return a - b; }
op = subtract;
std::cout << op(3, 4);  // -1
```

**When to use `std::function` vs templates:**

```cpp
// Template — zero overhead, but can't store in containers
template <typename F>
void apply(F func, int x) { func(x); }

// std::function — has overhead (heap allocation possible), but can be stored
void apply(std::function<void(int)> func, int x) { func(x); }
std::vector<std::function<void(int)>> callbacks;  // can store in containers
```

Use templates when you just need to accept a callable as a parameter. Use `std::function` when you need to **store** callables.

### 5. Lambdas as Callbacks

```cpp
class Button {
public:
    void set_on_click(std::function<void()> callback) {
        on_click_ = callback;
    }

    void click() {
        if (on_click_) on_click_();
    }

private:
    std::function<void()> on_click_;
};

Button btn;
btn.set_on_click([]() { std::cout << "clicked!\n"; });
btn.click();  // "clicked!"

int click_count = 0;
btn.set_on_click([&click_count]() {
    ++click_count;
    std::cout << "clicked " << click_count << " times\n";
});
btn.click();  // "clicked 1 times"
btn.click();  // "clicked 2 times"
```

### 6. Immediately Invoked Lambda (IIFE)

Call a lambda right where you define it — useful for complex initialization:

```cpp
const int value = [&]() {
    if (some_condition) return compute_a();
    else return compute_b();
}();  // note the () at the end — calls immediately

// value is const, initialized once, no temporary variables needed
```

### 7. Generic Lambdas (C++14)

Use `auto` in parameters to create a template-like lambda:

```cpp
auto print = [](const auto& x) { std::cout << x << "\n"; };
print(42);        // works with int
print("hello");   // works with const char*
print(3.14);      // works with double

auto add = [](auto a, auto b) { return a + b; };
add(1, 2);        // int
add(1.5, 2.5);    // double
add(std::string("a"), std::string("b"));  // string concatenation
```

### 8. Lambdas vs Function Pointers vs Functors

```cpp
// Function pointer — no state, C compatible
bool is_even_fp(int x) { return x % 2 == 0; }

// Functor — has state (from step 09)
struct IsGreaterThan {
    int threshold;
    bool operator()(int x) const { return x > threshold; }
};

// Lambda — concise, can capture state
int threshold = 5;
auto is_greater = [threshold](int x) { return x > threshold; };

// All three work with STL algorithms:
std::count_if(v.begin(), v.end(), is_even_fp);
std::count_if(v.begin(), v.end(), IsGreaterThan{5});
std::count_if(v.begin(), v.end(), is_greater);
```

Lambdas are essentially compiler-generated functors. The compiler creates an anonymous struct with `operator()` and your captured variables as members.

### 9. Capture Pitfalls

**Dangling reference:**
```cpp
std::function<int()> make_counter() {
    int count = 0;
    return [&count]() { return ++count; };  // DANGER: count is destroyed!
}
// The returned lambda captures a reference to a local variable.
// After make_counter returns, count is gone — undefined behavior.

// Fix: capture by value (with mutable)
std::function<int()> make_counter() {
    int count = 0;
    return [count]() mutable { return ++count; };  // OK — owns its own copy
}
```

**Capturing `this`:**
```cpp
class Timer {
public:
    void start() {
        // [this] captures the pointer — dangerous if Timer is destroyed
        callback_ = [this]() { std::cout << duration_ << "\n"; };

        // Safer in some contexts: [*this] copies the entire object (C++17)
    }
private:
    int duration_ = 0;
    std::function<void()> callback_;
};
```

---

## Exercises

1. **ex01_lambda_fundamentals.cpp** — Captures, mutable, closures
2. **ex02_functional_patterns.cpp** — Higher-order functions, callbacks, event system
3. **ex03_stl_with_lambdas.cpp** — Revisit STL algorithms using lambdas for everything
