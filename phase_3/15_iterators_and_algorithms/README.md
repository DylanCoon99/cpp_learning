# Step 15: Iterators and STL Algorithms

## Concepts

In step 13 you wrote your own generic algorithms (find, count, transform). The STL already has all of these — and many more — in `<algorithm>`. They all work through **iterators**, which are the glue between containers and algorithms.

### 1. What Is an Iterator?

An iterator is an object that points to an element in a container. It generalizes pointers — you can dereference (`*it`), advance (`++it`), and compare (`it != end`).

```cpp
std::vector<int> v = {10, 20, 30, 40, 50};

auto it = v.begin();    // iterator to first element
std::cout << *it;       // 10 (dereference)
++it;                    // advance to next
std::cout << *it;       // 20

auto end = v.end();     // iterator PAST the last element (not the last element!)
```

The range `[begin, end)` is a half-open interval — `end` is one past the last element. This convention is universal in C++ and makes empty ranges work naturally (`begin == end` means empty).

### 2. Iterator Categories

| Category | Operations | Containers |
|----------|-----------|------------|
| Input | `*it`, `++it`, `==`, `!=` | Input streams |
| Forward | Input + multi-pass | `forward_list`, `unordered_set/map` |
| Bidirectional | Forward + `--it` | `list`, `set`, `map` |
| Random Access | Bidirectional + `it + n`, `it[n]`, `it - it` | `vector`, `deque`, `array` |

Random access iterators work like pointers. Bidirectional iterators can only go forward and backward one step at a time. This matters because some algorithms (like `std::sort`) require random access iterators.

### 3. Common Iterator Operations

```cpp
std::vector<int> v = {10, 20, 30, 40, 50};

// begin/end
v.begin();     v.end();       // mutable iterators
v.cbegin();    v.cend();      // const iterators (can't modify through them)
v.rbegin();    v.rend();      // reverse iterators (iterate backwards)

// Advancing
auto it = v.begin();
std::advance(it, 3);           // move forward 3 steps (works for all iterator types)
auto it2 = std::next(it);     // return iterator to next element (doesn't modify it)
auto it3 = std::prev(it);     // return iterator to previous element

// Distance
int dist = std::distance(v.begin(), v.end());  // 5
```

### 4. STL Algorithms Overview

All in `#include <algorithm>` (some in `#include <numeric>`). They take iterator ranges, not containers:

```cpp
std::sort(v.begin(), v.end());              // not std::sort(v)
std::find(v.begin(), v.end(), target);      // not std::find(v, target)
```

This design lets the same algorithm work on any container, arrays, or even subranges.

### 5. Non-Modifying Algorithms

```cpp
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// find — returns iterator to first match (or end if not found)
auto it = std::find(v.begin(), v.end(), 5);
if (it != v.end()) std::cout << "found at index " << (it - v.begin());

// find_if — find by predicate
auto it2 = std::find_if(v.begin(), v.end(), [](int x) { return x > 7; });

// count / count_if
int n = std::count(v.begin(), v.end(), 1);         // 2
int m = std::count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });  // 2

// all_of, any_of, none_of
bool all_pos = std::all_of(v.begin(), v.end(), [](int x) { return x > 0; });   // true
bool has_neg = std::any_of(v.begin(), v.end(), [](int x) { return x < 0; });   // false
bool no_zeros = std::none_of(v.begin(), v.end(), [](int x) { return x == 0; }); // true

// for_each — apply function to each element
std::for_each(v.begin(), v.end(), [](int x) { std::cout << x << " "; });

// min_element, max_element — return iterators
auto min_it = std::min_element(v.begin(), v.end());
auto max_it = std::max_element(v.begin(), v.end());
std::cout << "min: " << *min_it << " max: " << *max_it;

// accumulate (in <numeric>)
#include <numeric>
int sum = std::accumulate(v.begin(), v.end(), 0);
```

### 6. Modifying Algorithms

```cpp
std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};

// sort
std::sort(v.begin(), v.end());                    // ascending
std::sort(v.begin(), v.end(), std::greater<>());  // descending
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // custom

// reverse
std::reverse(v.begin(), v.end());

// transform — apply function, write results to output
std::vector<int> doubled(v.size());
std::transform(v.begin(), v.end(), doubled.begin(), [](int x) { return x * 2; });

// transform in-place
std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });

// fill
std::fill(v.begin(), v.end(), 0);        // all zeros

// generate
std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });
// v = {0, 1, 2, 3, 4, 5, 6, 7}

// replace / replace_if
std::replace(v.begin(), v.end(), 0, 99);  // replace all 0s with 99
std::replace_if(v.begin(), v.end(), [](int x) { return x < 3; }, 0);

// remove / remove_if (doesn't actually erase — use with erase!)
auto new_end = std::remove(v.begin(), v.end(), 1);
v.erase(new_end, v.end());   // actually shrink the vector
// Or the C++20 way:
std::erase(v, 1);             // erase all 1s
std::erase_if(v, [](int x) { return x < 3; });  // erase if predicate

// unique — remove consecutive duplicates (sort first!)
std::sort(v.begin(), v.end());
auto last = std::unique(v.begin(), v.end());
v.erase(last, v.end());

// copy
std::vector<int> dest(v.size());
std::copy(v.begin(), v.end(), dest.begin());

// copy_if
std::vector<int> evens;
std::copy_if(v.begin(), v.end(), std::back_inserter(evens),
             [](int x) { return x % 2 == 0; });
```

### 7. `std::back_inserter`

When copying into an empty container, you can't use `dest.begin()` (nothing to overwrite). `std::back_inserter` creates an iterator that calls `push_back`:

```cpp
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst;  // empty!

// This would crash: std::copy(src.begin(), src.end(), dst.begin());
// This works:
std::copy(src.begin(), src.end(), std::back_inserter(dst));
```

### 8. Sorting with Custom Comparators

```cpp
struct Student {
    std::string name;
    double gpa;
};

std::vector<Student> students = {{"Alice", 3.8}, {"Bob", 3.5}, {"Carol", 3.9}};

// Sort by GPA descending
std::sort(students.begin(), students.end(),
    [](const Student& a, const Student& b) { return a.gpa > b.gpa; });

// Stable sort (preserves order of equal elements)
std::stable_sort(students.begin(), students.end(),
    [](const Student& a, const Student& b) { return a.gpa > b.gpa; });

// Partial sort (only sort the first N elements)
std::partial_sort(students.begin(), students.begin() + 2, students.end(),
    [](const Student& a, const Student& b) { return a.gpa > b.gpa; });
// First 2 are the top students, rest are unspecified order

// nth_element — find the Nth element as if sorted (O(n) average)
std::nth_element(students.begin(), students.begin() + 1, students.end(),
    [](const Student& a, const Student& b) { return a.gpa > b.gpa; });
// students[1] is the correct element; others are partitioned but not sorted
```

### 9. Binary Search (Sorted Ranges)

```cpp
std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// Must be sorted!

bool found = std::binary_search(v.begin(), v.end(), 5);  // true

auto lb = std::lower_bound(v.begin(), v.end(), 5);  // iterator to first >= 5
auto ub = std::upper_bound(v.begin(), v.end(), 5);  // iterator to first > 5

auto [lo, hi] = std::equal_range(v.begin(), v.end(), 5);  // both at once
```

### 10. Numeric Algorithms (`<numeric>`)

```cpp
#include <numeric>

std::vector<int> v = {1, 2, 3, 4, 5};

int sum = std::accumulate(v.begin(), v.end(), 0);         // 15
int product = std::accumulate(v.begin(), v.end(), 1, std::multiplies<>());  // 120

// partial_sum
std::vector<int> running(v.size());
std::partial_sum(v.begin(), v.end(), running.begin());     // {1, 3, 6, 10, 15}

// adjacent_difference
std::vector<int> diff(v.size());
std::adjacent_difference(v.begin(), v.end(), diff.begin()); // {1, 1, 1, 1, 1}

// inner_product (dot product)
std::vector<int> w = {2, 3, 4, 5, 6};
int dot = std::inner_product(v.begin(), v.end(), w.begin(), 0);  // 70

// iota — fill with incrementing values
std::iota(v.begin(), v.end(), 1);   // {1, 2, 3, 4, 5}
std::iota(v.begin(), v.end(), 10);  // {10, 11, 12, 13, 14}
```

---

## Exercises

1. **ex01_iterator_basics.cpp** — Practice iterator traversal and manipulation
2. **ex02_algorithm_survey.cpp** — Use 15+ STL algorithms on a dataset
3. **ex03_custom_sort.cpp** — Complex sorting with multiple criteria
4. **ex04_data_pipeline.cpp** — Chain algorithms to process data
5. **ex05_custom_iterator.cpp** — Build a class with its own begin()/end() iterators
