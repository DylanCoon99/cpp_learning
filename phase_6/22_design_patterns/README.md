# Step 22: Design Patterns in C++

## Concepts

Design patterns are reusable solutions to common software design problems. You've already used several without naming them (RAII, builder pattern in LogFilter, observer in EventEmitter). This step formalizes the most important ones in idiomatic C++.

### 1. Factory Pattern

Creates objects without exposing the instantiation logic. The caller asks for a type, the factory returns the right subclass.

```cpp
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape { /* ... */ };
class Rectangle : public Shape { /* ... */ };

// Factory function
std::unique_ptr<Shape> create_shape(const std::string& type) {
    if (type == "circle") return std::make_unique<Circle>();
    if (type == "rectangle") return std::make_unique<Rectangle>();
    return nullptr;
}

// Factory class (more flexible — can hold configuration)
class ShapeFactory {
public:
    using Creator = std::function<std::unique_ptr<Shape>()>;

    void register_type(const std::string& name, Creator creator) {
        creators_[name] = std::move(creator);
    }

    std::unique_ptr<Shape> create(const std::string& name) const {
        auto it = creators_.find(name);
        if (it == creators_.end()) return nullptr;
        return it->second();
    }

private:
    std::map<std::string, Creator> creators_;
};

// Usage
ShapeFactory factory;
factory.register_type("circle", []() { return std::make_unique<Circle>(); });
auto shape = factory.create("circle");
```

**When to use:** When you need to create objects based on runtime data (config files, user input, plugin systems).

### 2. Observer Pattern

Objects subscribe to events and get notified when they happen. You built this in step 16 (EventEmitter).

```cpp
class Observer {
public:
    virtual void on_event(const std::string& event, const std::string& data) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    void subscribe(std::shared_ptr<Observer> observer) {
        observers_.push_back(observer);
    }

    void notify(const std::string& event, const std::string& data) {
        // Use weak_ptr to avoid preventing observer destruction
        for (auto it = observers_.begin(); it != observers_.end(); ) {
            if (auto obs = it->lock()) {
                obs->on_event(event, data);
                ++it;
            } else {
                it = observers_.erase(it);  // observer was destroyed
            }
        }
    }

private:
    std::vector<std::weak_ptr<Observer>> observers_;
};
```

**When to use:** Event systems, GUI callbacks, pub/sub, model-view updates.

### 3. Strategy Pattern

Encapsulate algorithms behind an interface, swap them at runtime.

```cpp
// Strategy interface
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) = 0;
    virtual ~SortStrategy() = default;
};

class QuickSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::sort(data.begin(), data.end());
    }
};

class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        // bubble sort implementation
    }
};

// Context uses the strategy
class Sorter {
public:
    void set_strategy(std::unique_ptr<SortStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void sort(std::vector<int>& data) {
        if (strategy_) strategy_->sort(data);
    }

private:
    std::unique_ptr<SortStrategy> strategy_;
};
```

**Modern C++ alternative:** Use `std::function` instead of a class hierarchy:

```cpp
class Sorter {
public:
    using Strategy = std::function<void(std::vector<int>&)>;

    void set_strategy(Strategy s) { strategy_ = std::move(s); }
    void sort(std::vector<int>& data) { if (strategy_) strategy_(data); }

private:
    Strategy strategy_;
};

// Use with lambdas — no class hierarchy needed
sorter.set_strategy([](auto& data) { std::sort(data.begin(), data.end()); });
```

### 4. Singleton Pattern

Ensure a class has only one instance. Controversial — often overused.

```cpp
class Logger {
public:
    static Logger& instance() {
        static Logger logger;  // thread-safe in C++11+
        return logger;
    }

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx_);
        std::cout << msg << "\n";
    }

    // Prevent copying/moving
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() = default;  // private constructor
    std::mutex mtx_;
};

// Usage
Logger::instance().log("hello");
```

**When to use:** Sparingly. Logging, configuration, connection pools. Prefer dependency injection when possible.

### 5. Builder Pattern

Construct complex objects step by step. You used this for `LogFilter`.

```cpp
class HttpRequest {
public:
    class Builder {
    public:
        Builder& method(const std::string& m) { method_ = m; return *this; }
        Builder& url(const std::string& u) { url_ = u; return *this; }
        Builder& header(const std::string& key, const std::string& value) {
            headers_[key] = value;
            return *this;
        }
        Builder& body(const std::string& b) { body_ = b; return *this; }

        HttpRequest build() const {
            return HttpRequest(method_, url_, headers_, body_);
        }

    private:
        std::string method_ = "GET";
        std::string url_;
        std::map<std::string, std::string> headers_;
        std::string body_;
    };

private:
    HttpRequest(std::string method, std::string url,
                std::map<std::string, std::string> headers, std::string body)
        : method_(std::move(method)), url_(std::move(url)),
          headers_(std::move(headers)), body_(std::move(body)) {}

    std::string method_, url_, body_;
    std::map<std::string, std::string> headers_;
};

// Usage
auto request = HttpRequest::Builder()
    .method("POST")
    .url("https://api.example.com/data")
    .header("Content-Type", "application/json")
    .body("{\"key\": \"value\"}")
    .build();
```

### 6. Command Pattern

Encapsulate actions as objects. Supports undo/redo, queuing, logging.

```cpp
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class InsertTextCommand : public Command {
public:
    InsertTextCommand(std::string& doc, int pos, std::string text)
        : doc_(doc), pos_(pos), text_(std::move(text)) {}

    void execute() override { doc_.insert(pos_, text_); }
    void undo() override { doc_.erase(pos_, text_.length()); }

private:
    std::string& doc_;
    int pos_;
    std::string text_;
};

// Command history for undo/redo
class CommandHistory {
public:
    void execute(std::unique_ptr<Command> cmd) {
        cmd->execute();
        history_.push_back(std::move(cmd));
    }

    void undo() {
        if (!history_.empty()) {
            history_.back()->undo();
            history_.pop_back();
        }
    }

private:
    std::vector<std::unique_ptr<Command>> history_;
};
```

### 7. Decorator Pattern

Add behavior to objects dynamically by wrapping them.

```cpp
class Stream {
public:
    virtual void write(const std::string& data) = 0;
    virtual ~Stream() = default;
};

class FileStream : public Stream {
public:
    void write(const std::string& data) override {
        // write to file
    }
};

// Decorator base
class StreamDecorator : public Stream {
public:
    StreamDecorator(std::unique_ptr<Stream> inner) : inner_(std::move(inner)) {}
protected:
    std::unique_ptr<Stream> inner_;
};

class EncryptedStream : public StreamDecorator {
public:
    using StreamDecorator::StreamDecorator;
    void write(const std::string& data) override {
        std::string encrypted = encrypt(data);
        inner_->write(encrypted);
    }
private:
    std::string encrypt(const std::string& data) { /* ... */ return data; }
};

class CompressedStream : public StreamDecorator {
public:
    using StreamDecorator::StreamDecorator;
    void write(const std::string& data) override {
        std::string compressed = compress(data);
        inner_->write(compressed);
    }
private:
    std::string compress(const std::string& data) { /* ... */ return data; }
};

// Stack decorators
auto stream = std::make_unique<EncryptedStream>(
    std::make_unique<CompressedStream>(
        std::make_unique<FileStream>()
    )
);
stream->write("data");  // encrypts → compresses → writes to file
```

---

## Brief Reference: Template Metaprogramming

Not covered in exercises, but useful to know these exist:

**`constexpr if` (C++17)** — compile-time branching in templates:
```cpp
template <typename T>
std::string to_string(const T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
        return value;
    } else if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(value);
    } else {
        return "unknown";
    }
}
```

**Type traits** — query type properties at compile time:
```cpp
#include <type_traits>
std::is_integral_v<int>          // true
std::is_floating_point_v<double> // true
std::is_pointer_v<int*>          // true
std::is_same_v<int, int>         // true
std::is_base_of_v<Base, Derived> // true
```

**SFINAE** — "Substitution Failure Is Not An Error." Enable/disable template overloads based on type properties. Largely replaced by `constexpr if` and C++20 concepts in modern code.

## Brief Reference: Memory Model

Not covered in exercises, but useful to know:

**Placement new** — construct an object in pre-allocated memory:
```cpp
char buffer[sizeof(Widget)];
Widget* w = new (buffer) Widget();  // construct in buffer, no allocation
w->~Widget();                        // must manually destruct
```

**Custom allocators** — control how containers allocate memory. Used in game engines, embedded systems, and high-performance computing for arena allocation, pool allocation, etc.

**Alignment** — `alignas(16) int data[4];` ensures memory alignment for SIMD operations.

These are niche topics you'd learn when a specific project requires them.

---

## Exercise

One exercise: build a plugin-based data pipeline using multiple design patterns.
