# Step 07: Structs and Enums

## Concepts

You know structs from C. C++ structs are more powerful — they can have methods, constructors, and access specifiers (just like classes). The main difference between `struct` and `class` in C++ is the default access: `struct` is public by default, `class` is private. We'll use structs here and transition to classes in step 08.

### 1. Structs with Methods

```cpp
struct Point {
    double x;
    double y;

    // Member function (method)
    double distance_to(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // The 'const' after the parameter list means:
    // "this method does not modify the object"
    // Always mark methods const if they don't modify state.

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

Point p1{3.0, 4.0};   // aggregate initialization
p1.print();             // call method with dot syntax
```

This is a big step up from C structs, where you'd write `point_print(&p1)` as a free function.

### 2. Constructors

```cpp
struct Rectangle {
    double width;
    double height;

    // Default constructor
    Rectangle() : width(0), height(0) {}

    // Parameterized constructor
    Rectangle(double w, double h) : width(w), height(h) {}

    // The `: width(w), height(h)` part is the MEMBER INITIALIZER LIST.
    // It initializes members directly, which is more efficient than
    // assigning in the body. Prefer this style.

    double area() const { return width * height; }
    double perimeter() const { return 2 * (width + height); }
};

Rectangle r1;           // calls default constructor: 0x0
Rectangle r2(5, 3);     // calls parameterized constructor
Rectangle r3{5, 3};     // also calls parameterized constructor (brace init)
```

### 3. Member Initializer Lists

```cpp
struct Student {
    std::string name;
    int age;
    double gpa;

    // GOOD: member initializer list — initializes directly
    Student(const std::string& n, int a, double g)
        : name(n), age(a), gpa(g) {}

    // BAD (but works): assignment in body — default-constructs then assigns
    // Student(const std::string& n, int a, double g) {
    //     name = n;   // string was default-constructed to "", then overwritten
    //     age = a;
    //     gpa = g;
    // }
};
```

**Why prefer initializer lists:**
- More efficient (avoids default-construct-then-assign)
- Required for `const` members and reference members
- Required for members without default constructors

### 4. Aggregate Initialization

If a struct has no user-declared constructors, no private/protected members, and no virtual functions, it's an **aggregate** and can be initialized with `{}`:

```cpp
struct Color {
    uint8_t r, g, b;
};

Color red{255, 0, 0};           // aggregate init
Color blue = {0, 0, 255};       // also aggregate init

// C++20 designated initializers:
Color green{.r = 0, .g = 255, .b = 0};  // named fields!
```

Designated initializers (`.field = value`) are new in C++20. They exist in C99 too, but C++ has stricter rules: fields must be in declaration order.

### 5. Scoped Enums (`enum class`)

C has plain `enum`. C++ adds **scoped enums** which are type-safe:

```cpp
// C-style enum (still works, but avoid)
enum Color { RED, GREEN, BLUE };
int x = RED;           // RED leaks into enclosing scope
int y = RED + 1;       // implicitly converts to int — dangerous

// C++ scoped enum (preferred)
enum class Color { Red, Green, Blue };
Color c = Color::Red;   // must qualify with Color::
// int x = Color::Red;  // ERROR: no implicit conversion to int
int x = static_cast<int>(Color::Red);  // explicit conversion: OK
```

**Why prefer `enum class`:**
- Names don't leak into the enclosing scope
- No implicit conversion to int (prevents bugs)
- Can specify underlying type: `enum class Size : uint8_t { S, M, L, XL };`

### 6. Using Enums with Switch

```cpp
enum class Direction { North, South, East, West };

void move(Direction d) {
    switch (d) {
        case Direction::North: std::cout << "Moving north\n"; break;
        case Direction::South: std::cout << "Moving south\n"; break;
        case Direction::East:  std::cout << "Moving east\n";  break;
        case Direction::West:  std::cout << "Moving west\n";  break;
    }
    // Compiler warns if you miss a case — no default needed
}
```

### 7. Structs Containing Structs

```cpp
struct Address {
    std::string street;
    std::string city;
    std::string state;
    int zip;
};

struct Person {
    std::string name;
    int age;
    Address address;  // nested struct

    void print() const {
        std::cout << name << ", " << age << "\n"
                  << address.street << "\n"
                  << address.city << ", " << address.state
                  << " " << address.zip << "\n";
    }
};
```

### 8. `static` Members

```cpp
struct Counter {
    static int count;     // shared across ALL instances

    Counter() { ++count; }
    ~Counter() { --count; }  // destructor — called when object is destroyed

    static int get_count() { return count; }  // static method
};

int Counter::count = 0;   // must define static members outside the struct

Counter a, b, c;
std::cout << Counter::get_count();  // 3
```

### 9. Structured Bindings (C++17)

A modern way to unpack structs (similar to Python tuple unpacking or Go's multiple return):

```cpp
struct Point { double x, y; };

Point p{3.0, 4.0};
auto [px, py] = p;   // px = 3.0, py = 4.0

// Also works with std::pair and std::tuple:
#include <tuple>
auto [name, age] = std::make_pair(std::string("Dylan"), 28);
```

---

## Exercises

1. **ex01_shapes.cpp** — Struct with methods: shape types with area/perimeter
2. **ex02_enum_state.cpp** — Scoped enums for a state machine
3. **ex03_student_db.cpp** — Vector of structs: a mini student database
4. **ex04_deck_of_cards.cpp** — Enums + structs: model and shuffle a deck of cards
5. **ex05_ecs.cpp** — Simple Entity-Component system using structs and vectors
