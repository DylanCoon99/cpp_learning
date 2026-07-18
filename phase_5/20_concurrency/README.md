# Step 20: Concurrency

## Concepts

You know concurrency from Go (goroutines, channels, sync.Mutex). C++ has similar primitives but at a lower level — you manage threads directly.

### 1. `std::thread`

```cpp
#include <thread>

void do_work(int id) {
    std::cout << "Thread " << id << " running\n";
}

int main() {
    std::thread t1(do_work, 1);   // launch thread, pass argument
    std::thread t2(do_work, 2);

    t1.join();   // wait for t1 to finish
    t2.join();   // wait for t2 to finish
    // MUST join (or detach) every thread before it goes out of scope
    // Otherwise: std::terminate is called → crash
}
```

**join vs detach:**
- `join()` — block until the thread finishes (like Go's `wg.Wait()`)
- `detach()` — let it run independently (like a daemon goroutine). Rarely used — hard to manage.

**Launching with lambdas:**
```cpp
std::thread t([]() {
    std::cout << "hello from lambda thread\n";
});
t.join();
```

### 2. Data Races

When multiple threads access the same data and at least one writes, you have a **data race** — undefined behavior:

```cpp
int counter = 0;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        ++counter;  // DATA RACE — not atomic, not protected
    }
}

std::thread t1(increment);
std::thread t2(increment);
t1.join(); t2.join();
// counter is NOT 200000 — it's some random lower number
```

### 3. `std::mutex`

A mutex (mutual exclusion) protects shared data. Like Go's `sync.Mutex`:

```cpp
#include <mutex>

int counter = 0;
std::mutex mtx;

void increment() {
    for (int i = 0; i < 100000; ++i) {
        mtx.lock();
        ++counter;
        mtx.unlock();
    }
}
// Now counter is correctly 200000
```

**Problem:** If an exception is thrown between `lock()` and `unlock()`, the mutex is never unlocked → deadlock.

### 4. `std::lock_guard` — RAII for Mutexes

```cpp
void increment() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);  // locks on construction
        ++counter;
    }   // unlocks on destruction — even if exception is thrown
}
```

`lock_guard` is the RAII pattern applied to mutexes. **Always use `lock_guard` (or `unique_lock`) instead of raw `lock()`/`unlock()`.**

### 5. `std::unique_lock` — More Flexible Locking

```cpp
std::unique_lock<std::mutex> lock(mtx);  // locks immediately
lock.unlock();    // can manually unlock
lock.lock();      // and re-lock

// Can defer locking:
std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
// ... do non-critical work ...
lock.lock();   // lock when ready
```

Use `unique_lock` when you need to unlock/relock or use with condition variables. Use `lock_guard` for simple cases.

### 6. `std::scoped_lock` — Lock Multiple Mutexes (C++17)

```cpp
std::mutex mtx1, mtx2;

// Locks both without risk of deadlock
std::scoped_lock lock(mtx1, mtx2);
```

### 7. `std::atomic` — Lock-Free Thread Safety

For simple types (int, bool, pointers), atomics are faster than mutexes:

```cpp
#include <atomic>

std::atomic<int> counter{0};

void increment() {
    for (int i = 0; i < 100000; ++i) {
        ++counter;   // atomic — thread-safe without a mutex
    }
}
// counter is correctly 200000
```

**Common atomic operations:**
```cpp
std::atomic<int> x{0};
x.store(42);           // write
int val = x.load();    // read
x.fetch_add(1);        // add and return old value
x.fetch_sub(1);        // subtract and return old value
bool swapped = x.compare_exchange_strong(expected, desired);
```

Use atomics for counters, flags, and simple shared state. Use mutexes for complex shared data.

### 8. `std::condition_variable` — Thread Signaling

Like Go's channels for signaling between threads:

```cpp
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

// Producer thread
void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();   // wake up one waiting thread
}

// Consumer thread
void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });  // wait until ready == true
    // cv.wait atomically unlocks the mutex and sleeps
    // when notified, it re-locks and checks the predicate
    std::cout << "Data is ready!\n";
}
```

**Always use a predicate with `wait()`** — spurious wakeups can happen (the thread wakes up even without `notify`).

### 9. `std::async` and `std::future`

Higher-level than raw threads — launch a task and get the result later:

```cpp
#include <future>

int expensive_computation(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x;
}

// Launch async task
std::future<int> result = std::async(std::launch::async, expensive_computation, 42);

// Do other work while it computes...
std::cout << "Computing...\n";

// Get the result (blocks until ready)
int value = result.get();   // 1764
std::cout << "Result: " << value << "\n";
```

**Launch policies:**
- `std::launch::async` — always runs in a new thread
- `std::launch::deferred` — runs lazily when `.get()` is called (same thread)
- Default (no policy) — implementation decides

### 10. Thread-Safe Queue (Producer-Consumer Pattern)

A classic concurrency pattern — one or more threads produce data, others consume it:

```cpp
template <typename T>
class ThreadSafeQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.push(std::move(value));
        cv_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]{ return !queue_.empty(); });
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.empty();
    }

private:
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<T> queue_;
};
```

This is the C++ equivalent of a Go channel (unbuffered, blocking pop).

### 11. `std::this_thread` Utilities

```cpp
std::this_thread::sleep_for(std::chrono::milliseconds(100));
std::this_thread::sleep_until(some_time_point);
std::this_thread::yield();   // hint to scheduler: let other threads run
auto id = std::this_thread::get_id();   // unique thread ID
```

### 12. Common Pitfalls

- **Forgetting to join** → `std::terminate` crash
- **Data race** → undefined behavior (use mutex or atomic)
- **Deadlock** → two threads each waiting for the other's mutex. Use `scoped_lock` for multiple mutexes
- **Lock contention** → mutex held too long. Keep critical sections short
- **cout interleaving** → multiple threads writing to cout produces garbled output. Lock cout or use a logging queue

---

## Exercise

One exercise: build a thread-safe task executor.
