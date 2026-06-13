# Step 03: Control Flow

## Concepts

### 1. if / else if / else

Same as C, but with one C++17 addition — **init-statements**:

```cpp
// Standard (same as C)
if (x > 0) {
    // ...
} else if (x == 0) {
    // ...
} else {
    // ...
}

// C++17: if with initializer (like Go's if!)
// Variable 'result' is scoped to the if/else block
if (auto result = compute(); result > 0) {
    std::cout << "positive: " << result << "\n";
} else {
    std::cout << "non-positive: " << result << "\n";
}
// 'result' does NOT exist here
```

This is directly analogous to Go's `if err := doThing(); err != nil { ... }`.

### 2. switch

```cpp
switch (value) {
    case 1:
        std::cout << "one\n";
        break;              // MUST break — C++ falls through by default (like C)
    case 2:
        std::cout << "two\n";
        break;
    case 3:
        [[fallthrough]];    // C++17: explicit "I meant to fall through"
    case 4:
        std::cout << "three or four\n";
        break;
    default:
        std::cout << "other\n";
        break;
}
```

Key differences from Go:
- C++ `switch` **falls through by default** (Go does not)
- C++ requires `break` to stop fallthrough (Go requires `fallthrough` to enable it)
- `[[fallthrough]]` is a C++17 attribute that suppresses compiler warnings when you intentionally fall through

C++17 also added init-statements to switch:
```cpp
switch (auto val = getVal(); val) {
    case 1: /* ... */ break;
    default: break;
}
```

### 3. Loops

**while and do-while** (same as C):
```cpp
while (condition) {
    // ...
}

do {
    // runs at least once
} while (condition);
```

**for loop** (same as C):
```cpp
for (int i = 0; i < 10; ++i) {
    std::cout << i << "\n";
}
```

**Range-based for** (C++11 — like Python's `for x in list` or Go's `for _, x := range list`):
```cpp
#include <vector>
#include <string>

std::vector<int> nums = {1, 2, 3, 4, 5};

// By value (copies each element)
for (int n : nums) {
    std::cout << n << "\n";
}

// By const reference (no copy, read-only — preferred for non-trivial types)
for (const auto& n : nums) {
    std::cout << n << "\n";
}

// By reference (can modify elements)
for (auto& n : nums) {
    n *= 2;
}
```

**`++i` vs `i++`:** In C++ prefer `++i` (pre-increment). For integers they're identical, but for iterators `++i` can be more efficient because `i++` creates a temporary copy. It's a good habit.

### 4. break, continue

Same as C and Go. No labeled breaks in C++ (unlike Go).

### 5. Ternary Operator

```cpp
int x = (a > b) ? a : b;  // same as C
```

### 6. Comma Operator in for Loops

```cpp
// You can initialize/update multiple variables
for (int i = 0, j = 10; i < j; ++i, --j) {
    std::cout << i << " " << j << "\n";
}
```

---

## Exercises

1. **ex01_fizzbuzz.cpp** — Classic FizzBuzz (1 to 100)
2. **ex02_guessing.cpp** — Number guessing game with a loop
3. **ex03_switch.cpp** — Menu-driven calculator using switch
4. **ex04_patterns.cpp** — Print triangle/diamond patterns with nested loops
5. **ex05_collatz.cpp** — Collatz conjecture with if-init and range-for
