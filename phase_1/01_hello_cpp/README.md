# Step 01: Hello C++

## Concepts

### 1. The Compilation Model
Unlike Python (interpreted) or Go (single `go build` command), C++ compilation is a multi-stage pipeline:

```
source.cpp → [Preprocessor] → [Compiler] → source.o → [Linker] → executable
```

You compile with:
```bash
# Basic compilation
g++ -o program program.cpp

# With warnings and modern standard (get in this habit NOW)
g++ -std=c++20 -Wall -Wextra -o program program.cpp
```

`-Wall -Wextra` enables most warnings. **Always compile with warnings on.** Think of it like `go vet` but built into the compiler.

### 2. `#include` and the Preprocessor
C++ uses a preprocessor (like C). `#include` literally copy-pastes a header file into your source.

```cpp
#include <iostream>   // Standard library headers — angle brackets
#include "myfile.h"   // Your own headers — quotes
```

No module system like Go/Python imports (though C++20 modules exist, they're not widely adopted yet).

### 3. `main()`
```cpp
int main() {
    // program starts here
    return 0;  // 0 = success, non-zero = error (same as C)
}
```

Unlike C, you can omit `return 0;` — the compiler implicitly returns 0 from `main()`.

### 4. `std::cout` and `iostream`
C++ uses **streams** for I/O instead of `printf`:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world!" << std::endl;
    // std::cout — the standard output stream
    // <<        — the "insertion operator" (sends data into the stream)
    // std::endl — newline + flush (you can also use "\n" for just newline)
}
```

### 5. Namespaces
Everything in the standard library lives in the `std` namespace. That's why you write `std::cout`, not just `cout`.

```cpp
// You CAN do this, but don't in headers, and be cautious in source files:
using namespace std;
cout << "now you don't need std::" << endl;

// Better — import only what you need:
using std::cout;
using std::endl;
```

**Convention:** In this course, we'll always write `std::` explicitly. It's clearer and avoids name collisions. This is considered best practice in production C++.

### 6. Comments
```cpp
// Single-line comment (same as C, Go, etc.)

/* Multi-line
   comment */
```

### 7. `std::cin` for Input
```cpp
#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;              // reads one word (stops at whitespace)
    // or:
    std::getline(std::cin, name);  // reads entire line

    std::cout << "Hello, " << name << "!" << std::endl;
}
```

Note: `std::string` requires `#include <string>`. Unlike C's `char[]`, `std::string` manages its own memory.

---

## Exercises

Complete each exercise file in order. Compile and run to verify.

1. **ex01_hello.cpp** — Classic hello world
2. **ex02_greeting.cpp** — Read user input, print a greeting
3. **ex03_calculator.cpp** — Read two numbers, print their sum/difference/product/quotient
4. **ex04_temperature.cpp** — Fahrenheit to Celsius converter with formatted output
5. **ex05_multiline.cpp** — Practice with multiple `cout` statements, `\n` vs `endl`

### How to compile and run
```bash
g++ -std=c++20 -Wall -Wextra -o ex01 ex01_hello.cpp
./ex01
```
