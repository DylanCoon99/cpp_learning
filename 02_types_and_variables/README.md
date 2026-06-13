# Step 02: Types and Variables

## Concepts

### 1. Fundamental Types

C++ has the same primitive types as C, but with some additions and stronger typing:

```cpp
// Integer types (same as C, but with guaranteed-width alternatives)
int x = 42;            // at least 16 bits (usually 32)
long y = 100000L;      // at least 32 bits
long long z = 1LL;     // at least 64 bits
short s = 10;          // at least 16 bits

// If you need exact widths (like Go's int32, int64):
#include <cstdint>
int32_t a = 42;        // exactly 32 bits — like Go's int32
int64_t b = 100000;    // exactly 64 bits — like Go's int64
uint8_t c = 255;       // unsigned 8 bits — like Go's uint8/byte

// Floating point
float f = 3.14f;       // 32-bit (note the 'f' suffix)
double d = 3.14;       // 64-bit (default for decimal literals)

// Boolean
bool flag = true;      // true/false (C++ has a real bool, unlike old C)

// Character
char ch = 'A';         // single byte character
```

### 2. `auto` — Type Inference

C++11 introduced `auto`, which lets the compiler deduce the type. Similar to Go's `:=`:

```cpp
auto x = 42;           // int
auto pi = 3.14;        // double
auto name = std::string("Dylan");  // std::string
auto flag = true;      // bool

// Very useful when the type is obvious or verbose:
auto it = myMap.begin();  // instead of std::map<std::string, int>::iterator
```

**When to use `auto`:**
- When the type is obvious from the right-hand side
- When the type is long/verbose
- In range-based for loops

**When NOT to use `auto`:**
- When it makes the code less readable (what type is `auto result = compute();`?)
- When you want to be explicit about a conversion

### 3. `const` — Immutability

`const` means "this value cannot be changed after initialization." You know `const` from C, but in C++ it's used much more pervasively:

```cpp
const int max_size = 100;        // compile-time constant
const std::string greeting = "hello";  // runtime constant

max_size = 200;  // ERROR: cannot assign to const variable
```

**`constexpr` — compile-time constants:**
```cpp
constexpr int square(int x) { return x * x; }
constexpr int val = square(5);  // computed at compile time — val is 25

// constexpr is stronger than const:
// - const: "I promise not to change this" (value may be set at runtime)
// - constexpr: "This MUST be computable at compile time"
```

There's no direct equivalent in Go or Python. The closest is Go's `const`, but `constexpr` can apply to functions too.

### 4. Type Conversions

C++ has four cast operators (unlike C's single `(type)value` cast):

```cpp
// Implicit conversions (same as C — happen automatically)
int x = 3.14;          // 3 — truncates, compiler may warn
double y = 42;          // 42.0 — safe widening

// C-style cast (works but AVOID in C++)
int a = (int)3.14;     // don't do this

// C++ casts — use these instead:
int b = static_cast<int>(3.14);   // explicit numeric conversion
// static_cast is the one you'll use 95% of the time

// Others (you'll learn these later):
// dynamic_cast    — for polymorphic class hierarchies
// const_cast      — to add/remove const (rarely needed)
// reinterpret_cast — raw bit reinterpretation (like unsafe pointer casts in C)
```

**Rule of thumb:** If you need a cast, use `static_cast<T>(value)`. If you find yourself reaching for `reinterpret_cast`, think twice.

### 5. Initialization Syntax

C++ has multiple ways to initialize variables. This is one of C++'s warts — too many options:

```cpp
int a = 5;      // copy initialization (C-style, fine for simple types)
int b(5);       // direct initialization (rarely used for simple types)
int c{5};       // brace initialization (C++11, preferred)
int d = {5};    // copy-list initialization

// Why prefer braces {}?
// They prevent narrowing conversions:
int x = 3.14;   // compiles (silently truncates to 3) — DANGEROUS
int y{3.14};    // ERROR: narrowing conversion — SAFE
```

For this course, use whichever feels natural, but know that `{}` is the "safest" form.

### 6. `sizeof` and Type Sizes

```cpp
#include <iostream>

std::cout << sizeof(int) << std::endl;       // typically 4
std::cout << sizeof(double) << std::endl;    // typically 8
std::cout << sizeof(char) << std::endl;      // always 1
std::cout << sizeof(bool) << std::endl;      // typically 1
```

### 7. `using` Type Aliases

```cpp
// C-style typedef (still works):
typedef unsigned long ulong;

// C++11 style (preferred — clearer syntax):
using ulong = unsigned long;
using Byte = uint8_t;
using StringVec = std::vector<std::string>;
```

The `using` form is preferred because it reads left-to-right and works with templates (which `typedef` struggles with).

---

## Exercises

1. **ex01_sizes.cpp** — Print the size in bytes of every fundamental type
2. **ex02_auto.cpp** — Practice `auto` with different types, print what you get
3. **ex03_const.cpp** — Work with `const` and `constexpr`
4. **ex04_conversions.cpp** — Practice type conversions and observe narrowing
5. **ex05_overflow.cpp** — Explore integer overflow behavior
