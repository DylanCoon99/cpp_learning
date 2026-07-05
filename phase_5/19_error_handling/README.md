# Step 19: Error Handling

## Concepts

You've been using exceptions casually (`throw std::runtime_error(...)`) throughout the course. This step covers the full picture: when to use exceptions, when not to, and the alternatives.

### 1. The Exception Hierarchy

All standard exceptions inherit from `std::exception`:

```
std::exception
├── std::logic_error
│   ├── std::invalid_argument
│   ├── std::out_of_range
│   ├── std::length_error
│   └── std::domain_error
├── std::runtime_error
│   ├── std::overflow_error
│   ├── std::underflow_error
│   └── std::range_error
└── std::bad_alloc          (thrown by new on failure)
    std::bad_cast           (thrown by dynamic_cast on failure)
```

**`logic_error`** = programmer mistake (could have been prevented). Bug in the code.
**`runtime_error`** = environment problem (file missing, network down). Can't prevent, must handle.

### 2. Throwing and Catching

```cpp
// Throw
void divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("Division by zero");
    return a / b;
}

// Catch
try {
    divide(10, 0);
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << "\n";
} catch (const std::exception& e) {
    std::cerr << "Unexpected: " << e.what() << "\n";
} catch (...) {
    std::cerr << "Unknown exception\n";
}
```

**Key rules:**
- Catch by `const reference` (avoids slicing, avoids copy)
- Catch more specific exceptions first (derived before base)
- `catch (...)` catches anything — use as a last resort
- `e.what()` returns the error message string

### 3. Custom Exceptions

```cpp
class DatabaseError : public std::runtime_error {
public:
    DatabaseError(const std::string& msg, int code)
        : std::runtime_error(msg), error_code_(code) {}

    int error_code() const { return error_code_; }

private:
    int error_code_;
};

// Throw
throw DatabaseError("Connection failed", 503);

// Catch
try { ... }
catch (const DatabaseError& e) {
    std::cerr << e.what() << " (code: " << e.error_code() << ")\n";
}
```

Inherit from `std::runtime_error` or `std::logic_error`. Add extra fields as needed.

### 4. `noexcept`

You've seen `noexcept` on move constructors. It's a promise that a function won't throw:

```cpp
void safe_function() noexcept {
    // if this throws, std::terminate() is called — program crashes
}

// Conditional noexcept:
template <typename T>
void swap(T& a, T& b) noexcept(noexcept(T(std::move(a)))) {
    // noexcept if T's move constructor is noexcept
}

// Check at compile time:
static_assert(noexcept(safe_function()));
```

**When to use `noexcept`:**
- Move constructors/assignment (required for vector optimization)
- Swap functions
- Destructors (implicitly noexcept — never throw from a destructor)
- Simple getters, size(), empty()

### 5. Exception Safety Guarantees

| Guarantee | Meaning | Example |
|-----------|---------|---------|
| **No-throw** | Never throws | Destructors, swap, move ops |
| **Strong** | If it throws, state is unchanged (rollback) | Copy-and-swap assignment |
| **Basic** | If it throws, no leaks, object is valid but state may differ | Most STL operations |
| **No guarantee** | Anything can happen | Avoid this |

RAII and smart pointers give you basic guarantee automatically — resources are always cleaned up even if exceptions fly.

### 6. Exceptions vs Error Codes

**Exceptions** (C++ default):
```cpp
int parse_int(const std::string& s) {
    // throws on failure
    return std::stoi(s);
}
```

**Error codes** (C-style, also used in some C++ APIs):
```cpp
enum class ParseError { None, InvalidInput, Overflow };

ParseError parse_int(const std::string& s, int& result) {
    try {
        result = std::stoi(s);
        return ParseError::None;
    } catch (...) {
        return ParseError::InvalidInput;
    }
}
```

**`std::optional`** (C++17 — for "might not have a value"):
```cpp
#include <optional>

std::optional<int> parse_int(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return std::nullopt;  // no value
    }
}

auto result = parse_int("42");
if (result) {
    std::cout << *result << "\n";  // 42
} else {
    std::cout << "parse failed\n";
}
```

**`std::expected`** (C++23 — value OR error):
```cpp
#include <expected>

std::expected<int, std::string> parse_int(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (const std::exception& e) {
        return std::unexpected(e.what());
    }
}

auto result = parse_int("abc");
if (result) {
    std::cout << *result << "\n";
} else {
    std::cout << "Error: " << result.error() << "\n";
}
```

**When to use what:**
| Approach | Use When |
|----------|----------|
| Exceptions | Truly exceptional situations (file not found, out of memory, invariant violated) |
| `std::optional` | Value might legitimately not exist (find, parse, lookup) |
| Error codes/enum | Performance-critical paths, C interop, embedded systems |
| `std::expected` | You want to return either a value or a detailed error (C++23) |

### 7. RAII and Exception Safety

```cpp
// BAD — leak if process() throws
void bad() {
    int* data = new int[100];
    process(data);     // if this throws, data is never deleted
    delete[] data;
}

// GOOD — RAII handles cleanup automatically
void good() {
    auto data = std::make_unique<int[]>(100);
    process(data.get());   // if this throws, unique_ptr still cleans up
}
```

This is why RAII and smart pointers exist — they make exception safety automatic.

### 8. `std::optional` In Depth

```cpp
#include <optional>

std::optional<std::string> find_user(int id) {
    if (id == 1) return "Alice";
    if (id == 2) return "Bob";
    return std::nullopt;
}

auto user = find_user(1);

// Check and access
if (user.has_value()) { ... }
if (user) { ... }               // same thing
std::string name = *user;       // access (undefined if empty!)
std::string name = user.value(); // access (throws if empty)
std::string name = user.value_or("Unknown");  // default if empty
```

`std::optional` is like Go's `, ok` pattern or Rust's `Option<T>`. It's the idiomatic C++ way to say "this might not have a value" without using pointers or sentinel values.

---

## Exercise

One exercise: build a config file parser with comprehensive error handling.
