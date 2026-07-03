# Phase 3 Project: In-Memory Database

A query-able, in-memory database engine that exercises smart pointers, templates, STL containers, iterators, algorithms, and lambdas.

## Overview

Build a generic, type-safe table system that stores records, supports queries, and handles relationships — all in memory. This is a simplified version of what SQLite does, using everything from Phase 3.

## Core Components

### `Table<T>` — Generic Record Storage

A templated container that stores records and provides query operations.

```cpp
template <typename T>
class Table {
public:
    // Insert a record, returns its ID
    int insert(T record);

    // Remove by ID
    bool remove(int id);

    // Get by ID (returns nullptr if not found)
    T* get(int id);
    const T* get(int id) const;

    // Query — returns all records matching a predicate
    std::vector<const T*> where(std::function<bool(const T&)> predicate) const;

    // Get all records
    std::vector<const T*> all() const;

    // Aggregate operations
    int count() const;
    int count_where(std::function<bool(const T&)> predicate) const;

    // Apply a function to all records matching a predicate
    void update_where(std::function<bool(const T&)> predicate,
                      std::function<void(T&)> updater);

    // Sort records by a comparator, return sorted pointers
    std::vector<const T*> order_by(std::function<bool(const T&, const T&)> comparator) const;

    // Return the first N records matching a predicate
    std::vector<const T*> top_n(int n, std::function<bool(const T&, const T&)> comparator) const;

    // Print all records (requires T to have operator<<)
    void print_all() const;

private:
    std::map<int, T> records_;   // ID → record
    int next_id_ = 1;
};
```

### Record Types

Define at least these record structs:

```cpp
struct Employee {
    std::string name;
    std::string department;
    double salary;
    int manager_id;  // ID of another Employee, or 0 if none

    friend std::ostream& operator<<(std::ostream& os, const Employee& e);
};

struct Project {
    std::string name;
    std::string status;  // "active", "completed", "on_hold"
    double budget;

    friend std::ostream& operator<<(std::ostream& os, const Project& p);
};

struct Assignment {
    int employee_id;
    int project_id;
    std::string role;  // "lead", "developer", "tester"

    friend std::ostream& operator<<(std::ostream& os, const Assignment& a);
};
```

### `Database` — Holds All Tables

```cpp
class Database {
public:
    Table<Employee> employees;
    Table<Project> projects;
    Table<Assignment> assignments;

    // Cross-table queries:

    // Find all employees on a specific project
    std::vector<const Employee*> employees_on_project(int project_id) const;

    // Find all projects for a specific employee
    std::vector<const Project*> projects_for_employee(int employee_id) const;

    // Find the manager of an employee
    const Employee* manager_of(int employee_id) const;

    // Find all direct reports of a manager
    std::vector<const Employee*> direct_reports(int manager_id) const;

    // Department summary: name, headcount, total salary, avg salary
    void department_summary() const;
};
```

## Required Features

### 1. Generic Table Operations
- Insert, remove, get by ID
- `where()` with lambda predicates
- `update_where()` to modify records in bulk
- `order_by()` for sorted results
- `top_n()` for limited results

### 2. Cross-Table Queries
- Join through `Assignment` to connect `Employee` and `Project`
- Navigate `manager_id` to find reporting chains
- Aggregate across tables (e.g., total budget of projects an employee works on)

### 3. Lambda-Driven Queries
All queries should use lambdas as predicates:
```cpp
// Find high earners in Engineering
auto results = db.employees.where([](const Employee& e) {
    return e.department == "Engineering" && e.salary > 100000;
});

// Sort by salary descending
auto sorted = db.employees.order_by([](const Employee& a, const Employee& b) {
    return a.salary > b.salary;
});

// Give everyone in Marketing a 10% raise
db.employees.update_where(
    [](const Employee& e) { return e.department == "Marketing"; },
    [](Employee& e) { e.salary *= 1.10; }
);
```

### 4. Smart Pointer Usage
- Use `std::unique_ptr` or `std::shared_ptr` if you store records on the heap
- Or use the map-based approach (records stored by value in map, return raw pointers for observation)
- The important thing: no `new`/`delete` anywhere

## Example Usage

```cpp
int main() {
    Database db;

    // Seed data
    int alice = db.employees.insert({"Alice",  "Engineering", 120000, 0});
    int bob   = db.employees.insert({"Bob",    "Engineering", 95000,  alice});
    int carol = db.employees.insert({"Carol",  "Marketing",   88000,  0});
    int dan   = db.employees.insert({"Dan",    "Engineering", 105000, alice});

    int p1 = db.projects.insert({"Project Alpha", "active",    500000});
    int p2 = db.projects.insert({"Project Beta",  "active",    300000});
    int p3 = db.projects.insert({"Project Gamma", "completed", 200000});

    db.assignments.insert({alice, p1, "lead"});
    db.assignments.insert({bob,   p1, "developer"});
    db.assignments.insert({bob,   p2, "developer"});
    db.assignments.insert({dan,   p1, "tester"});
    db.assignments.insert({carol, p2, "lead"});

    // Queries
    std::cout << "=== Engineers earning > 100k ===\n";
    auto high_earners = db.employees.where([](const Employee& e) {
        return e.department == "Engineering" && e.salary > 100000;
    });
    for (auto* e : high_earners) std::cout << *e << "\n";

    std::cout << "\n=== Employees on Project Alpha ===\n";
    for (auto* e : db.employees_on_project(p1)) std::cout << *e << "\n";

    std::cout << "\n=== Alice's direct reports ===\n";
    for (auto* e : db.direct_reports(alice)) std::cout << *e << "\n";

    std::cout << "\n=== Top 3 earners ===\n";
    auto top3 = db.employees.top_n(3, [](const Employee& a, const Employee& b) {
        return a.salary > b.salary;
    });
    for (auto* e : top3) std::cout << *e << "\n";

    std::cout << "\n=== Department Summary ===\n";
    db.department_summary();

    // Bulk update
    db.employees.update_where(
        [](const Employee& e) { return e.department == "Marketing"; },
        [](Employee& e) { e.salary *= 1.10; }
    );

    std::cout << "\n=== After Marketing raise ===\n";
    db.employees.print_all();
}
```

## Architecture Notes

- `Table<T>` is fully generic — it knows nothing about Employee, Project, etc.
- All filtering/sorting logic lives in lambdas passed by the caller
- Cross-table joins are handled in `Database`, which knows about all tables
- `map<int, T>` gives O(log n) lookup by ID and stable pointers
- Return `const T*` from queries — callers observe, don't own
- Use `update_where` for modifications — keeps the mutation path clear

## Getting Started

```bash
g++ -std=c++20 -Wall -Wextra -o db database.cpp
./db
```
