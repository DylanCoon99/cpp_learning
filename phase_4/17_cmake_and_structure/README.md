# Step 17: CMake and Project Structure

## Concepts

Up to now, you've compiled everything with a single `g++` command against one source file. Real C++ projects have dozens or hundreds of files. CMake is the standard build system that manages this complexity.

### 1. Why CMake?

Without CMake, building a multi-file project looks like:
```bash
g++ -std=c++20 -Wall -c src/main.cpp -o build/main.o
g++ -std=c++20 -Wall -c src/database.cpp -o build/database.o
g++ -std=c++20 -Wall -c src/table.cpp -o build/table.o
g++ build/main.o build/database.o build/table.o -o build/app
```

With CMake:
```bash
cmake -B build
cmake --build build
```

CMake generates the build commands for you, handles dependencies, and works cross-platform.

### 2. Basic CMakeLists.txt

Every CMake project has a `CMakeLists.txt` in the root:

```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create an executable from source files
add_executable(myapp
    src/main.cpp
    src/database.cpp
    src/table.cpp
)

# Add include directories (so #include "database.h" works)
target_include_directories(myapp PRIVATE include)
```

### 3. Building with CMake

```bash
# Configure — generates build files in a 'build' directory
cmake -B build

# Build — compiles everything
cmake --build build

# Run
./build/myapp

# Clean rebuild
cmake --build build --clean-first
```

The `-B build` flag means "put build files in the `build/` directory." This keeps your source tree clean — never mix build artifacts with source code.

### 4. Header/Source Separation

In C++, code is split into **header files** (.h/.hpp) and **source files** (.cpp):

```
project/
├── CMakeLists.txt
├── include/
│   ├── database.h      ← declarations (interface)
│   └── table.h
└── src/
    ├── main.cpp
    ├── database.cpp     ← definitions (implementation)
    └── table.cpp
```

**Header file** (database.h) — declares the interface:
```cpp
#pragma once    // include guard — prevents double inclusion

#include <string>
#include <vector>

class Database {
public:
    void insert(const std::string& key, int value);
    int get(const std::string& key) const;
    bool contains(const std::string& key) const;
    int size() const;

private:
    std::vector<std::pair<std::string, int>> data_;
};
```

**Source file** (database.cpp) — defines the implementation:
```cpp
#include "database.h"
#include <algorithm>

void Database::insert(const std::string& key, int value) {
    data_.push_back({key, value});
}

int Database::get(const std::string& key) const {
    auto it = std::find_if(data_.begin(), data_.end(),
        [&key](const auto& p) { return p.first == key; });
    if (it != data_.end()) return it->second;
    throw std::runtime_error("Key not found: " + key);
}

// ... etc
```

**main.cpp** — uses the header:
```cpp
#include "database.h"
#include <iostream>

int main() {
    Database db;
    db.insert("age", 25);
    std::cout << db.get("age") << "\n";
}
```

### 5. `#pragma once` vs Include Guards

Both prevent a header from being included twice:

```cpp
// Modern (preferred):
#pragma once

// Traditional:
#ifndef DATABASE_H
#define DATABASE_H
// ... header contents ...
#endif
```

`#pragma once` is simpler and supported by all major compilers. Use it.

### 6. What Goes in Headers vs. Source Files

| In the header (.h) | In the source (.cpp) |
|--------------------|--------------------|
| Class declarations | Method definitions |
| Function declarations | Function definitions |
| Inline functions | |
| Template definitions (must be in header!) | |
| Constants, enums, type aliases | |
| `#include` for types used in declarations | `#include` for types used only in implementation |

**Key rule:** Headers declare interfaces. Source files implement them. This minimizes recompilation — changing an implementation only recompiles that one source file.

**Template exception:** Template code must go in headers because the compiler needs to see the full definition to instantiate it. You can use a `.hpp` extension to signal "this header contains implementation."

### 7. Forward Declarations

Instead of including a full header, you can forward-declare a type if you only use pointers or references to it:

```cpp
// database.h
class Table;  // forward declaration — don't need to #include "table.h"

class Database {
    Table* table_;  // only a pointer — forward declaration is enough
    // Table table_;  // full object — would need #include "table.h"
};
```

This reduces compile times by minimizing header dependencies.

### 8. CMake Targets and Libraries

For larger projects, split code into libraries:

```cmake
# Create a library (compiled separately, linked into executables)
add_library(mylib
    src/database.cpp
    src/table.cpp
)
target_include_directories(mylib PUBLIC include)

# Create an executable that uses the library
add_executable(myapp src/main.cpp)
target_link_libraries(myapp PRIVATE mylib)
```

`PUBLIC` vs `PRIVATE`:
- `PUBLIC` — the include dirs propagate to anything that links against this library
- `PRIVATE` — only this target uses them

### 9. CMake Variables and Options

```cmake
# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Or per-target (preferred):
target_compile_options(myapp PRIVATE -Wall -Wextra)

# Build type (Debug/Release)
# Debug: no optimization, debug symbols
# Release: optimization, no debug symbols
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Custom option
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
```

### 10. Subdirectories

Large projects organize CMake files hierarchically:

```
project/
├── CMakeLists.txt           ← top-level
├── src/
│   ├── CMakeLists.txt       ← builds the library
│   └── ...
├── app/
│   ├── CMakeLists.txt       ← builds the executable
│   └── main.cpp
└── tests/
    ├── CMakeLists.txt       ← builds tests
    └── ...
```

Top-level CMakeLists.txt:
```cmake
cmake_minimum_required(VERSION 3.20)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)
```

### 11. The Compilation Model — How It All Fits Together

```
                    ┌─────────────┐
  database.h ──────►│  database.o │
  database.cpp ────►│  (compile)  │──┐
                    └─────────────┘  │
                                     │    ┌──────────┐
                    ┌─────────────┐  ├───►│   myapp  │
  table.h ─────────►│   table.o   │──┘    │  (link)  │
  table.cpp ───────►│  (compile)  │──┐    └──────────┘
                    └─────────────┘  │         ▲
                                     │         │
                    ┌─────────────┐  │         │
  main.cpp ────────►│   main.o    │──┘─────────┘
  (includes .h)    │  (compile)  │
                    └─────────────┘
```

Each .cpp file is compiled independently into an .o file. The linker combines them into the final executable. Headers are copy-pasted by the preprocessor — they're not compiled separately.

---

## Exercises

Build each exercise as a proper multi-file CMake project.

1. **ex01_first_cmake/** — Convert a single-file program to a CMake project
2. **ex02_multi_file/** — Split a program into headers, sources, and a library
3. **ex03_calculator_lib/** — Build a reusable math library with a separate app
