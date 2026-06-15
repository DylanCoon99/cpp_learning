# Step 06: Strings and Arrays

## Concepts

### 1. `std::string` — The C++ String

You've been using `std::string` already. Let's go deeper.

```cpp
#include <string>

// Construction
std::string s1 = "hello";            // from C-string literal
std::string s2("world");             // direct init
std::string s3(5, 'x');              // "xxxxx" — repeat char
std::string s4 = s1;                 // copy
std::string s5 = s1 + " " + s2;     // concatenation with +

// Size
s1.size();      // 5 (same as .length())
s1.empty();     // false

// Access
s1[0];          // 'h' — no bounds checking (like C)
s1.at(0);       // 'h' — WITH bounds checking (throws std::out_of_range)
s1.front();     // 'h'
s1.back();      // 'o'

// Modification
s1 += " world";         // append
s1.append(" !");         // append
s1.push_back('!');       // append single char
s1.insert(5, ",");       // insert at position
s1.erase(5, 1);          // erase 1 char at position 5
s1.replace(0, 5, "Hi");  // replace "hello" with "Hi"
s1.clear();               // empty the string

// Searching
s1 = "hello world";
s1.find("world");        // 6 (index where found)
s1.find("xyz");          // std::string::npos (not found)
s1.find('o');            // 4
s1.rfind('o');           // 7 (reverse find — last occurrence)
s1.substr(6, 5);         // "world" (pos, length)

// Comparison
s1 == s2;       // content comparison (unlike C where you need strcmp)
s1 < s2;        // lexicographic comparison
s1.compare(s2); // like strcmp: returns <0, 0, or >0
```

### 2. C-String Interop

```cpp
std::string cpp_str = "hello";
const char* c_str = cpp_str.c_str();  // get C-string pointer

// C-string to std::string
const char* raw = "world";
std::string from_c(raw);              // implicit conversion
std::string from_c2 = raw;            // also works

// When interfacing with C APIs:
// printf("%s", cpp_str.c_str());   // need .c_str() for C functions
```

### 3. String Iteration

```cpp
std::string s = "hello";

// Index-based
for (size_t i = 0; i < s.size(); ++i) {
    std::cout << s[i];
}

// Range-based (preferred)
for (char c : s) {
    std::cout << c;
}

// By reference (to modify)
for (char& c : s) {
    c = std::toupper(c);  // #include <cctype>
}
```

### 4. `std::array` — Fixed-Size Array (C++11)

A safer replacement for C arrays. Size is known at compile time.

```cpp
#include <array>

std::array<int, 5> arr = {1, 2, 3, 4, 5};

arr.size();       // 5 (always knows its size — unlike C arrays)
arr[0];           // 1 (no bounds check)
arr.at(0);        // 1 (bounds checked)
arr.front();      // 1
arr.back();       // 5
arr.fill(0);      // set all elements to 0

// Works with range-based for
for (const auto& n : arr) {
    std::cout << n << " ";
}

// Can be passed to functions without decaying to pointer
void print(const std::array<int, 5>& a);  // size is part of the type
```

**`std::array` vs C array:**
| Feature | C array (`int a[5]`) | `std::array<int, 5>` |
|---------|---------------------|---------------------|
| Knows its size | No (decays to pointer) | Yes (`.size()`) |
| Bounds checking | No | Yes (`.at()`) |
| Assignable | No | Yes (`a = b`) |
| Works with STL | Partially | Fully |

### 5. `std::vector` — Dynamic Array

You've used this a bit already. Here's the full picture.

```cpp
#include <vector>

// Construction
std::vector<int> v1;                    // empty
std::vector<int> v2(5);                 // 5 elements, all 0
std::vector<int> v3(5, 42);            // 5 elements, all 42
std::vector<int> v4 = {1, 2, 3, 4, 5}; // initializer list

// Size and capacity
v4.size();       // 5 — number of elements
v4.capacity();   // >= 5 — allocated storage (may be larger)
v4.empty();      // false
v4.resize(10);   // now has 10 elements (new ones are 0)
v4.reserve(100); // pre-allocate capacity for 100 elements (size unchanged)

// Access
v4[0];           // no bounds check
v4.at(0);        // bounds checked
v4.front();
v4.back();

// Modification
v4.push_back(6);        // add to end — O(1) amortized
v4.pop_back();           // remove last — O(1)
v4.insert(v4.begin() + 2, 99);  // insert at index 2 — O(n)
v4.erase(v4.begin() + 2);       // erase at index 2 — O(n)
v4.clear();              // remove all elements

// Shrink
v4.shrink_to_fit();      // request to reduce capacity to match size
```

**How `vector` grows:**
When you `push_back` past capacity, the vector allocates new (usually 2x) storage, copies/moves everything over, and frees the old storage. This is why `push_back` is "amortized O(1)" — occasional expensive reallocations, but averages out.

### 6. `std::vector<std::string>` — Vectors of Strings

```cpp
std::vector<std::string> words = {"hello", "world", "foo"};

// Sort (preview — we'll cover algorithms in step 15)
#include <algorithm>
std::sort(words.begin(), words.end());  // alphabetical

// Find
auto it = std::find(words.begin(), words.end(), "world");
if (it != words.end()) {
    std::cout << "found: " << *it << "\n";
}
```

### 7. 2D Vectors

```cpp
// Vector of vectors — dynamic 2D array
std::vector<std::vector<int>> grid(3, std::vector<int>(4, 0));
// 3 rows, 4 columns, all zeros

grid[1][2] = 42;

for (const auto& row : grid) {
    for (int val : row) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}
```

---

## Exercises

1. **ex01_string_ops.cpp** — String manipulation and searching
2. **ex02_array_vs_vector.cpp** — Compare std::array and std::vector behavior
3. **ex03_word_counter.cpp** — Count words and characters in user input
4. **ex04_matrix.cpp** — 2D vector operations (transpose, multiply)
5. **ex05_string_toolkit.cpp** — Build a string utility library
