# Step 10: Inheritance and Polymorphism

## Concepts

### 1. Basic Inheritance

A derived class inherits members from a base class. Similar concept to embedding in Go, but with actual language-level inheritance.

```cpp
class Animal {
public:
    Animal(const std::string& name) : name_(name) {}
    std::string name() const { return name_; }
    void eat() const { std::cout << name_ << " is eating\n"; }
private:
    std::string name_;
};

class Dog : public Animal {
public:
    Dog(const std::string& name, const std::string& breed)
        : Animal(name), breed_(breed) {}   // MUST call base constructor

    std::string breed() const { return breed_; }
    void fetch() const { std::cout << name() << " fetches!\n"; }
private:
    std::string breed_;
};

Dog d("Rex", "Lab");
d.eat();      // inherited from Animal
d.fetch();    // defined in Dog
d.name();     // inherited from Animal
```

### 2. Access Specifiers with Inheritance

```cpp
class Base {
public:      // accessible everywhere
    int a;
protected:   // accessible in Base AND derived classes
    int b;
private:     // accessible ONLY in Base
    int c;
};

class Derived : public Base {
    void foo() {
        a = 1;   // OK — public
        b = 2;   // OK — protected, we're a derived class
        c = 3;   // ERROR — private to Base
    }
};
```

The `public` in `: public Base` means "keep the base class access levels as-is." You'll almost always use `public` inheritance.

### 3. Virtual Functions and Polymorphism

Without `virtual`, the base class version is always called through a base pointer/reference:

```cpp
class Shape {
public:
    // NOT virtual
    std::string type() const { return "Shape"; }
};

class Circle : public Shape {
public:
    std::string type() const { return "Circle"; }  // hides base version
};

Circle c;
Shape& ref = c;     // base reference to derived object
ref.type();          // "Shape" — calls Shape::type(), NOT Circle::type()!
```

With `virtual`, the **actual object type** determines which function runs:

```cpp
class Shape {
public:
    virtual std::string type() const { return "Shape"; }
};

class Circle : public Shape {
public:
    std::string type() const override { return "Circle"; }
};

Circle c;
Shape& ref = c;
ref.type();          // "Circle" — polymorphism! Correct version called.
```

This is the core of polymorphism: **a base pointer/reference calling the derived class's method**.

### 4. `override` and `final`

```cpp
class Base {
public:
    virtual void speak() const { std::cout << "...\n"; }
    virtual void move() { std::cout << "moving\n"; }
};

class Derived : public Base {
public:
    void speak() const override {    // override: compiler checks this actually overrides
        std::cout << "hello\n";
    }

    // void speak() override { }     // ERROR: missing 'const' — doesn't match base
                                      // override catches this mistake!

    void move() final {               // final: no further derived class can override this
        std::cout << "derived moving\n";
    }
};

class SubDerived : public Derived {
public:
    // void move() override { }      // ERROR: move() is final in Derived
};
```

**Always use `override`** when overriding. It catches subtle bugs (mismatched signatures).

### 5. Pure Virtual Functions and Abstract Classes

A **pure virtual function** has no implementation — derived classes MUST override it:

```cpp
class Shape {
public:
    virtual double area() const = 0;       // pure virtual — no body
    virtual double perimeter() const = 0;  // pure virtual
    virtual std::string type() const = 0;  // pure virtual

    // Can still have non-pure virtuals and regular methods:
    virtual void print() const {
        std::cout << type() << ": area=" << area() << "\n";
    }
};

// Shape s;  // ERROR: cannot instantiate abstract class

class Circle : public Shape {
public:
    explicit Circle(double r) : radius_(r) {}

    double area() const override { return 3.14159 * radius_ * radius_; }
    double perimeter() const override { return 2 * 3.14159 * radius_; }
    std::string type() const override { return "Circle"; }

private:
    double radius_;
};

Circle c(5);
c.print();     // "Circle: area=78.5398" — uses inherited print() which calls our overrides
```

An abstract class is like a Go **interface** — it defines what derived classes must implement. But unlike Go interfaces, C++ abstract classes can also contain state and default implementations.

### 6. Virtual Destructors

**Critical rule:** If a class has virtual functions, its destructor MUST be virtual.

```cpp
class Base {
public:
    virtual ~Base() = default;   // virtual destructor
    virtual void speak() const = 0;
};

class Derived : public Base {
public:
    Derived() : data_(new int[100]) {}
    ~Derived() override { delete[] data_; }
    void speak() const override { std::cout << "hi\n"; }
private:
    int* data_;
};

Base* ptr = new Derived();
delete ptr;   // Without virtual ~Base(), Derived's destructor NEVER runs → MEMORY LEAK
              // With virtual ~Base(), Derived's destructor runs correctly
```

**Rule of thumb:** If you have any virtual function, add `virtual ~ClassName() = default;`.

### 7. Polymorphism with Pointers and References

```cpp
// Store different derived types in one container:
std::vector<std::unique_ptr<Shape>> shapes;  // unique_ptr — preview of step 12
shapes.push_back(std::make_unique<Circle>(5));
shapes.push_back(std::make_unique<Rectangle>(3, 4));
shapes.push_back(std::make_unique<Triangle>(3, 4, 5));

// Polymorphic call — each shape's own area() is called:
for (const auto& s : shapes) {
    s->print();   // calls Circle::print(), Rectangle::print(), etc.
}

// For now, you can use raw pointers (we'll switch to smart pointers in step 12):
std::vector<Shape*> shapes;
shapes.push_back(new Circle(5));
// ... don't forget to delete each one when done
```

### 8. Slicing Problem

```cpp
Circle c(5);
Shape s = c;     // SLICING: copies only the Shape part, Circle data is lost!
s.area();        // calls Shape::area(), not Circle::area()
                 // If area() is pure virtual, this won't even compile

// Solution: always use pointers or references for polymorphism
Shape& ref = c;  // OK — no slicing
Shape* ptr = &c; // OK — no slicing
```

**Never store polymorphic objects by value in containers.** Use pointers.

### 9. `dynamic_cast` — Runtime Type Checking

```cpp
Shape* s = get_some_shape();

// Try to cast to Circle — returns nullptr if s isn't actually a Circle
if (Circle* c = dynamic_cast<Circle*>(s)) {
    std::cout << "It's a circle with radius " << c->radius() << "\n";
} else {
    std::cout << "Not a circle\n";
}
```

`dynamic_cast` requires the base class to have at least one virtual function. Use sparingly — frequent `dynamic_cast` usually means your design needs rethinking.

### 10. Inheritance vs. Composition

**Inheritance** ("is-a"): A Dog IS an Animal
**Composition** ("has-a"): A Car HAS an Engine

```cpp
// Inheritance — Dog IS an Animal
class Dog : public Animal { ... };

// Composition — Car HAS an Engine
class Car {
    Engine engine_;   // member, not base class
    // ...
};
```

**Prefer composition over inheritance** when the relationship isn't truly "is-a." This is the same principle as in Go, where embedding is used sparingly.

---

## Exercises

1. **ex01_shapes.cpp** — Shape hierarchy with polymorphism
2. **ex02_employees.cpp** — Employee types with virtual pay calculation
3. **ex03_vehicles.cpp** — Vehicle hierarchy with abstract base and dynamic_cast
4. **ex04_logger.cpp** — Logger hierarchy with composition vs inheritance
5. **ex05_game_objects.cpp** — Game object hierarchy pulling together everything
