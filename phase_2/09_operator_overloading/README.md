# Step 09: Operator Overloading

## Concepts

You got a preview of this in step 08 with `Vec2::operator+`. Now we'll cover it fully. Operator overloading lets your classes work with built-in syntax like `+`, `==`, `<<`, and `[]`.

### 1. Why Overload Operators?

Without overloading:
```cpp
Vec2 c = a.add(b);
if (a.equals(b)) { ... }
std::cout << a.to_string();
```

With overloading:
```cpp
Vec2 c = a + b;
if (a == b) { ... }
std::cout << a;
```

The second form is more natural and lets your types feel like built-in types.

### 2. Member vs. Non-Member (Friend) Overloads

**Member function:** left operand is `this`
```cpp
class Vec2 {
public:
    // a + b  →  a.operator+(b)
    Vec2 operator+(const Vec2& rhs) const {
        return Vec2(x_ + rhs.x_, y_ + rhs.y_);
    }
};
```

**Non-member (friend) function:** needed when the left operand isn't your class
```cpp
class Vec2 {
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};

// std::cout << v  →  operator<<(std::cout, v)
// Can't be a member because the left operand is ostream, not Vec2
std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "(" << v.x_ << ", " << v.y_ << ")";
    return os;  // return stream for chaining: cout << a << b
}
```

**When to use which:**
- **Member:** `=`, `[]`, `()`, `->`, compound assignment (`+=`, `-=`)
- **Non-member (friend):** `<<`, `>>`, symmetric binary ops where you want `int + Vec2` to work
- **Non-member (non-friend):** when you can implement using public interface only

### 3. Arithmetic Operators

```cpp
class Fraction {
public:
    Fraction(int num, int den) : num_(num), den_(den) {}

    // Compound assignment (member, modifies this, returns reference)
    Fraction& operator+=(const Fraction& rhs) {
        num_ = num_ * rhs.den_ + rhs.num_ * den_;
        den_ = den_ * rhs.den_;
        return *this;
    }

    // Binary + (implement in terms of +=)
    Fraction operator+(const Fraction& rhs) const {
        Fraction result = *this;   // copy
        result += rhs;             // reuse +=
        return result;
    }

    // Unary minus
    Fraction operator-() const {
        return Fraction(-num_, den_);
    }

private:
    int num_, den_;
};
```

**Best practice:** Implement `+` in terms of `+=`. This avoids code duplication and ensures consistency. Same pattern for `-`/`-=`, `*`/`*=`, `/`/`/=`.

### 4. Comparison Operators

```cpp
class Date {
public:
    bool operator==(const Date& rhs) const {
        return year_ == rhs.year_ && month_ == rhs.month_ && day_ == rhs.day_;
    }

    bool operator!=(const Date& rhs) const {
        return !(*this == rhs);    // implement in terms of ==
    }

    bool operator<(const Date& rhs) const {
        if (year_ != rhs.year_) return year_ < rhs.year_;
        if (month_ != rhs.month_) return month_ < rhs.month_;
        return day_ < rhs.day_;
    }

    bool operator>(const Date& rhs) const  { return rhs < *this; }
    bool operator<=(const Date& rhs) const { return !(rhs < *this); }
    bool operator>=(const Date& rhs) const { return !(*this < rhs); }
};
```

**C++20 spaceship operator** (much simpler):
```cpp
#include <compare>

class Date {
public:
    auto operator<=>(const Date& rhs) const = default;
    // This single line generates ==, !=, <, >, <=, >= automatically!
    // Works when all members are themselves comparable.
};

// Or custom:
class Date {
public:
    auto operator<=>(const Date& rhs) const {
        if (auto cmp = year_ <=> rhs.year_; cmp != 0) return cmp;
        if (auto cmp = month_ <=> rhs.month_; cmp != 0) return cmp;
        return day_ <=> rhs.day_;
    }
    bool operator==(const Date& rhs) const = default;
};
```

### 5. Stream Operators (`<<` and `>>`)

```cpp
class Point {
public:
    Point(double x, double y) : x_(x), y_(y) {}

    // Output: must be friend (or non-member with getters)
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x_ << ", " << p.y_ << ")";
        return os;
    }

    // Input
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x_ >> p.y_;
        return is;
    }

private:
    double x_, y_;
};

Point p(3, 4);
std::cout << "Point: " << p << std::endl;   // "Point: (3, 4)"

Point q(0, 0);
std::cin >> q;   // reads two doubles
```

### 6. Subscript Operator (`[]`)

```cpp
class IntArray {
public:
    // Non-const version (allows modification)
    int& operator[](int index) {
        return data_[index];
    }

    // Const version (read-only)
    const int& operator[](int index) const {
        return data_[index];
    }

private:
    int* data_;
};

IntArray arr(10);
arr[3] = 42;              // calls non-const []
const IntArray& ref = arr;
int x = ref[3];            // calls const []
```

### 7. Function Call Operator (`()`) — Functors

```cpp
class Multiplier {
public:
    explicit Multiplier(int factor) : factor_(factor) {}

    int operator()(int value) const {
        return value * factor_;
    }

private:
    int factor_;
};

Multiplier triple(3);
std::cout << triple(10);   // 30 — looks like a function call!
std::cout << triple(7);    // 21
```

Objects with `operator()` are called **functors**. They're like function pointers but can carry state. Lambdas (step 16) are actually compiler-generated functors.

### 8. Increment/Decrement (`++`, `--`)

```cpp
class Counter {
public:
    explicit Counter(int val = 0) : val_(val) {}

    // Pre-increment: ++c
    Counter& operator++() {
        ++val_;
        return *this;
    }

    // Post-increment: c++ (note the dummy int parameter)
    Counter operator++(int) {
        Counter old = *this;   // save current
        ++val_;                // increment
        return old;            // return old value
    }

private:
    int val_;
};
```

The `int` parameter in post-increment is a dummy — it just distinguishes the two overloads. Prefer pre-increment (`++c`) when you don't need the old value.

### 9. What NOT to Overload

- Don't overload operators in surprising ways (`+` should add, not subtract)
- Don't overload `&&`, `||`, or `,` — they lose short-circuit behavior
- Don't overload `&` (address-of) unless you have a very good reason

---

## Exercises

1. **ex01_fraction.cpp** — Fraction class with full arithmetic
2. **ex02_vector2d.cpp** — 2D vector class with all operators
3. **ex03_matrix.cpp** — Matrix class with arithmetic and stream operators
4. **ex04_bigint.cpp** — Big integer class (arbitrary precision addition)
5. **ex05_custom_container.cpp** — Container with [], iterator-like ++, and ()
