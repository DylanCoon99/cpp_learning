# Step 14: STL Containers

## Concepts

You've used `std::vector` extensively. The STL (Standard Template Library) has many more containers, each optimized for different use cases. This step covers the major ones.

### 1. Container Categories

| Category | Containers | Access Pattern |
|----------|-----------|---------------|
| Sequence | `vector`, `deque`, `list`, `array`, `forward_list` | Ordered by insertion |
| Associative (sorted) | `map`, `set`, `multimap`, `multiset` | Sorted by key |
| Unordered | `unordered_map`, `unordered_set`, `unordered_multimap`, `unordered_multiset` | Hash table |
| Adaptor | `stack`, `queue`, `priority_queue` | Restricted access |

### 2. `std::map` — Sorted Key-Value Store

Like Go's `map` or Python's `dict`, but **sorted by key** (uses a balanced binary tree internally).

```cpp
#include <map>

std::map<std::string, int> ages;

// Insert
ages["Alice"] = 30;
ages["Bob"] = 25;
ages.insert({"Carol", 28});
ages.emplace("Dan", 35);          // constructs in-place (more efficient)

// Access
int a = ages["Alice"];             // 30
int b = ages.at("Bob");           // 25 (throws if not found)
// ages["Unknown"] creates an entry with value 0! Use .at() or .find() instead.

// Check existence
if (ages.count("Alice")) { /* exists */ }
if (ages.contains("Alice")) { /* C++20 */ }

// Find (returns iterator)
auto it = ages.find("Bob");
if (it != ages.end()) {
    std::cout << it->first << ": " << it->second << "\n";
    // first = key, second = value
}

// Iterate (sorted by key!)
for (const auto& [name, age] : ages) {    // structured bindings (C++17)
    std::cout << name << " is " << age << "\n";
}
// Output: Alice, Bob, Carol, Dan (alphabetical)

// Remove
ages.erase("Bob");

// Size
ages.size();
ages.empty();
```

**Complexity:**
- Insert, find, erase: O(log n)
- Iteration: O(n) in sorted order

### 3. `std::unordered_map` — Hash Map

Same interface as `map`, but uses a hash table. **Not sorted**, but faster for lookups.

```cpp
#include <unordered_map>

std::unordered_map<std::string, int> scores;
scores["Alice"] = 95;
scores["Bob"] = 87;

// Same interface as map:
scores.find("Alice");
scores.count("Bob");
scores.contains("Alice");  // C++20

// Iteration order is NOT guaranteed
for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << "\n";
}
```

**Complexity:**
- Insert, find, erase: O(1) average, O(n) worst case
- Use when you don't need sorted order and want speed

**When to use which:**
- Need sorted iteration? → `map`
- Need fastest lookup? → `unordered_map`
- In practice, `unordered_map` is used more often

### 4. `std::set` — Sorted Unique Collection

Stores unique values in sorted order. Like a `map` without values.

```cpp
#include <set>

std::set<int> s = {5, 3, 1, 4, 2, 3, 1};  // duplicates removed
// s contains: {1, 2, 3, 4, 5}

s.insert(6);         // adds 6
s.insert(3);         // no effect — 3 already exists
s.erase(2);          // removes 2
s.count(3);          // 1 (exists) or 0 (doesn't)
s.contains(3);       // C++20: true

// Iterate (sorted)
for (int x : s) {
    std::cout << x << " ";  // 1 3 4 5 6
}

// Find
auto it = s.find(4);
if (it != s.end()) {
    std::cout << "found: " << *it << "\n";
}
```

### 5. `std::unordered_set` — Hash Set

```cpp
#include <unordered_set>

std::unordered_set<std::string> words;
words.insert("hello");
words.insert("world");
words.insert("hello");   // no effect — duplicate
// words.size() == 2

words.contains("hello");  // true
```

### 6. `std::deque` — Double-Ended Queue

Like `vector` but efficient insertion/removal at **both** ends.

```cpp
#include <deque>

std::deque<int> dq = {2, 3, 4};

dq.push_front(1);    // [1, 2, 3, 4]
dq.push_back(5);     // [1, 2, 3, 4, 5]
dq.pop_front();       // [2, 3, 4, 5]
dq.pop_back();        // [2, 3, 4]

dq[0];                // random access works (like vector)
dq.front();
dq.back();
```

**vs vector:** vector is O(n) for push_front (shifts everything). deque is O(1) for both ends. But vector has better cache performance for iteration.

### 7. `std::list` — Doubly Linked List

```cpp
#include <list>

std::list<int> lst = {1, 2, 3, 4, 5};

lst.push_front(0);
lst.push_back(6);

// No random access! lst[2] does NOT work.
// Must iterate:
for (int x : lst) {
    std::cout << x << " ";
}

// Efficient insert/erase anywhere (given an iterator):
auto it = std::next(lst.begin(), 2);  // iterator to 3rd element
lst.insert(it, 99);   // insert 99 before 3rd element
lst.erase(it);         // erase 3rd element

lst.sort();            // built-in sort (can't use std::sort — no random access)
lst.reverse();
lst.unique();          // remove consecutive duplicates (sort first!)
```

### 8. `std::multimap` and `std::multiset`

Allow **duplicate keys/values:**

```cpp
#include <map>

std::multimap<std::string, int> grades;
grades.insert({"Alice", 90});
grades.insert({"Alice", 85});  // OK — duplicates allowed
grades.insert({"Alice", 95});

// Find all entries for a key:
auto range = grades.equal_range("Alice");
for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << " ";  // 85 90 95
}

grades.count("Alice");   // 3
```

### 9. Container Adaptors

These wrap an underlying container and restrict the interface:

```cpp
#include <stack>
#include <queue>

// Stack (LIFO) — wraps deque by default
std::stack<int> s;
s.push(1); s.push(2); s.push(3);
s.top();    // 3
s.pop();    // removes 3

// Queue (FIFO) — wraps deque by default
std::queue<int> q;
q.push(1); q.push(2); q.push(3);
q.front();  // 1
q.back();   // 3
q.pop();    // removes 1

// Priority Queue (max heap)
std::priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(4); pq.push(1); pq.push(5);
pq.top();   // 5 (largest)
pq.pop();   // removes 5
pq.top();   // 4
```

### 10. Choosing the Right Container

| Need | Container |
|------|-----------|
| Dynamic array, random access | `vector` |
| Fast push/pop at both ends | `deque` |
| Frequent insert/erase in middle | `list` |
| Key-value lookup, sorted | `map` |
| Key-value lookup, fast | `unordered_map` |
| Unique sorted values | `set` |
| Unique values, fast lookup | `unordered_set` |
| LIFO | `stack` |
| FIFO | `queue` |
| Sorted retrieval | `priority_queue` |

**Default to `vector`** unless you have a specific reason to use something else. It's the most cache-friendly and fastest for most use cases.

### 11. Structured Bindings with Containers (C++17)

```cpp
std::map<std::string, int> m = {{"a", 1}, {"b", 2}};

// Old way:
for (const auto& pair : m) {
    std::cout << pair.first << ": " << pair.second << "\n";
}

// C++17 structured bindings:
for (const auto& [key, value] : m) {
    std::cout << key << ": " << value << "\n";
}

// Also works with insert return value:
auto [it, inserted] = m.insert({"c", 3});
// it = iterator to element, inserted = bool (true if new)
```

---

## Exercises

1. **ex01_map_basics.cpp** — Word frequency counter using map and unordered_map
2. **ex02_set_operations.cpp** — Set operations: union, intersection, difference
3. **ex03_phone_book.cpp** — Multi-field lookup with map and multimap
4. **ex04_task_queue.cpp** — Priority task system using queue and priority_queue
5. **ex05_container_benchmark.cpp** — Compare performance of different containers
