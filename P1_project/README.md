# Phase 1 Project: Contact Book

A command-line contact management application that exercises everything from Phase 1.

## Overview

Build a fully functional contact book that stores contacts in memory and lets the user manage them through a text menu. This is a realistic small utility — the kind of thing you'd write as a quick tool for yourself.

## Data Model

```cpp
enum class Category { Personal, Work, Family, Other };

struct Contact {
    int id;
    std::string first_name;
    std::string last_name;
    std::string phone;
    std::string email;
    Category category;
};
```

## Required Features

### 1. Menu System
Display a numbered menu and loop until the user quits:
```
=== Contact Book ===
1. Add contact
2. View all contacts
3. Search contacts
4. Edit contact
5. Delete contact
6. View by category
7. Statistics
8. Export (print formatted)
9. Quit
```

### 2. Add Contact
- Prompt for each field (first name, last name, phone, email, category)
- Auto-assign an incrementing ID
- Category selection via a sub-menu (1=Personal, 2=Work, 3=Family, 4=Other)
- Store in a `std::vector<Contact>`

### 3. View All Contacts
- Print all contacts in a formatted table
- Include ID, full name, phone, email, and category
- Handle the empty case ("No contacts found.")

### 4. Search Contacts
- Ask the user for a search term
- Search across first name, last name, email, AND phone
- Case-insensitive search (convert both to lowercase before comparing)
- Use `std::string::find()` for substring matching
- Display all matches

### 5. Edit Contact
- Ask for the contact ID to edit
- Find it using a pointer-returning function (like the student DB exercise)
- Show current values, let the user type new ones
- Allow pressing Enter to keep the current value:
  - Read with `std::getline` — if the input is empty, don't change the field
  - Hint: after `std::cin >> id`, call `std::cin.ignore()` before `getline`
    to consume the leftover newline

### 6. Delete Contact
- Ask for the contact ID
- Confirm before deleting ("Are you sure? y/n")
- Remove from the vector using `std::erase` or iterator-based removal:
  ```cpp
  // Find and erase by iterator:
  for (auto it = contacts.begin(); it != contacts.end(); ++it) {
      if (it->id == target_id) {
          contacts.erase(it);
          break;
      }
  }
  ```

### 7. View by Category
- Sub-menu to pick a category
- Filter and display only contacts in that category
- Show count: "Found 3 Work contacts:"

### 8. Statistics
- Total number of contacts
- Count per category
- Most common email domain (extract everything after '@')
  - Hint: `email.substr(email.find('@') + 1)`

### 9. Export
- Print all contacts in a clean, formatted layout suitable for copying:
  ```
  ┌────────────────────────────────────┐
  │ Dylan Coon                         │
  │ Phone: 555-1234                    │
  │ Email: dylan@example.com           │
  │ Category: Work                     │
  └────────────────────────────────────┘
  ```
  (You can use simpler box characters like +, -, | if you prefer)

## Architecture Guidelines

- **Organize with functions.** Don't put all logic in main. Each menu option should be its own function.
- **Use const references** for read-only parameters.
- **Use pointers** where null is meaningful (find functions).
- **Use `enum class`** for Category, with a to_string helper.
- **Use `const`** on methods and variables where appropriate.
- **Keep it in one file** for now — multi-file organization comes later.

## Suggested Function Signatures

```cpp
// Helpers
std::string category_to_string(Category c);
std::string to_lower(const std::string& s);

// Core operations
void add_contact(std::vector<Contact>& contacts, int& next_id);
void view_all(const std::vector<Contact>& contacts);
void search_contacts(const std::vector<Contact>& contacts);
void edit_contact(std::vector<Contact>& contacts);
void delete_contact(std::vector<Contact>& contacts);
void view_by_category(const std::vector<Contact>& contacts);
void print_stats(const std::vector<Contact>& contacts);
void export_contacts(const std::vector<Contact>& contacts);

// Lookup
Contact* find_by_id(std::vector<Contact>& contacts, int id);
```

## Bonus Features (optional)
- Sort contacts by name before displaying
- Validate email format (must contain '@' and '.')
- Validate phone format (digits, dashes, and optional parentheses)
- Add a "favorite" boolean field, with a "View favorites" option
- Seed the app with 5-10 sample contacts on startup for easier testing

## Getting Started

```bash
# Create your file and start coding:
g++ -std=c++20 -Wall -Wextra -o contacts contacts.cpp
./contacts
```
