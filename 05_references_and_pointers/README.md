# Step 05: References and Pointers

## Concepts

You already know pointers from C. C++ keeps all of that and adds **references** — a cleaner, safer alternative for most use cases. This step is about understanding when to use which.

### 1. References Revisited

A reference is an **alias** — another name for an existing variable. Not a new object, not a pointer. An alias.

```cpp
int x = 42;
int& ref = x;   // ref IS x — same memory location

ref = 100;       // x is now 100
std::cout << x;  // prints 100

// Address is the same:
std::cout << &x;    // same address
std::cout << &ref;  // same address
```

**Critical rules:**
```cpp
int& r;          // ERROR: references MUST be initialized
int& r = x;     // OK
int& r = 42;    // ERROR: can't bind non-const ref to a literal

const int& r = 42;  // OK: const ref CAN bind to a temporary/literal
                     // (the compiler extends the temporary's lifetime)
```

References cannot be reassigned — once bound, they're bound for life:
```cpp
int a = 1, b = 2;
int& ref = a;
ref = b;         // this does NOT rebind ref — it assigns b's value to a
                 // now a == 2, and ref still refers to a
```

### 2. References vs. Pointers — When to Use Which

| Feature | Reference (`T&`) | Pointer (`T*`) |
|---------|------------------|----------------|
| Can be null | No | Yes (`nullptr`) |
| Can be reassigned | No | Yes |
| Syntax | Clean (`ref.member`) | Explicit (`ptr->member`) |
| Must be initialized | Yes | No (but should be) |
| Can do arithmetic | No | Yes (`ptr++`) |

**Use references when:**
- The thing must always exist (no null case)
- You don't need to reassign it
- Function parameters and return values (most common use)

**Use pointers when:**
- It might be null (optional/absent value)
- You need to reassign what you're pointing to
- You need pointer arithmetic (arrays, low-level memory)
- Interfacing with C APIs

In modern C++, raw pointers for ownership are discouraged — that's what smart pointers are for (step 12). Raw pointers are fine for **non-owning** observation.

### 3. `nullptr` (C++11)

```cpp
int* p = nullptr;    // C++: use nullptr (not NULL, not 0)

if (p == nullptr) {  // or just: if (!p)
    std::cout << "null\n";
}

// nullptr has its own type: std::nullptr_t
// This avoids the ambiguity bugs that NULL (which is just 0) caused in C:
void f(int);
void f(int*);
f(NULL);     // ambiguous! NULL is 0, could match f(int)
f(nullptr);  // unambiguous — calls f(int*)
```

### 4. Const with Pointers — Reading the Declarations

This is the most confusing part of C/C++ pointer syntax. Read right-to-left:

```cpp
int x = 10;

// pointer to int — can change both pointer and value
int* p1 = &x;
*p1 = 20;        // OK
p1 = nullptr;    // OK

// pointer to const int — can change pointer, NOT value
const int* p2 = &x;    // or: int const* p2 = &x;  (same thing)
*p2 = 20;        // ERROR
p2 = nullptr;    // OK

// const pointer to int — can change value, NOT pointer
int* const p3 = &x;
*p3 = 20;        // OK
p3 = nullptr;    // ERROR

// const pointer to const int — can change NEITHER
const int* const p4 = &x;
*p4 = 20;        // ERROR
p4 = nullptr;    // ERROR
```

**Trick:** Read the declaration from right to left:
- `const int*` → "pointer to int that is const" → can't change the int
- `int* const` → "const pointer to int" → can't change the pointer

### 5. Reference to Pointer, Pointer to Pointer

```cpp
// Reference to a pointer — useful when a function needs to modify a pointer
void allocate(int*& ptr) {
    ptr = new int(42);  // modifies the caller's pointer
}

int* p = nullptr;
allocate(p);       // p now points to a new int
std::cout << *p;   // 42
delete p;          // must free (we'll cover this properly in later steps)

// Pointer to pointer (same as C)
int** pp = &p;
```

### 6. Dangling References and Pointers

```cpp
// DANGLING REFERENCE — undefined behavior:
int& bad() {
    int local = 42;
    return local;    // WARNING: returning reference to local variable
}                    // local is destroyed, reference is dangling

// DANGLING POINTER — same idea:
int* also_bad() {
    int local = 42;
    return &local;   // same problem with pointer
}
```

The compiler will usually warn about these. Always heed those warnings.

### 7. `new` and `delete` (Brief Introduction)

C++ has `new`/`delete` instead of `malloc`/`free`. They call constructors/destructors (important for classes later).

```cpp
int* p = new int(42);      // allocate + initialize
int* arr = new int[10];    // allocate array

delete p;                  // free single object
delete[] arr;              // free array — MUST use delete[] for arrays

// In modern C++, you should almost NEVER use raw new/delete.
// Use smart pointers instead (step 12). But you need to know these exist.
```

---

## Exercises

1. **ex01_ref_basics.cpp** — Reference fundamentals and const references
2. **ex02_ptr_ref_compare.cpp** — Side-by-side comparison of pointers and references
3. **ex03_const_correctness.cpp** — Practice with const pointers and const references
4. **ex04_new_delete.cpp** — Manual memory management with new/delete
5. **ex05_linked_list.cpp** — Build a simple singly-linked list using pointers
