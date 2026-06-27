// Exercise 3: Phone Book with Multiple Lookup Methods
//
// Task: Build a phone book that demonstrates different map patterns.
//
// Define:
//   struct Contact {
//       std::string name;
//       std::string phone;
//       std::string email;
//       std::string city;
//   };
//
// Part A — Primary lookup by name:
//   Use std::map<std::string, Contact> (key = name)
//   - Add 8-10 contacts
//   - Look up by name
//   - Print all contacts sorted by name
//
// Part B — Reverse lookup by phone:
//   Build a second map: std::unordered_map<std::string, std::string>
//   mapping phone → name
//   - Given a phone number, find the contact name, then look up full contact
//   - This pattern (secondary index) is common in real applications
//
// Part C — Group by city using multimap:
//   Build: std::multimap<std::string, std::string> (city → name)
//   - Multiple contacts can be in the same city
//   - Use equal_range to find all contacts in a given city
//   - Print contacts grouped by city
//
// Part D — Interactive menu:
//   Build a simple menu:
//     1. Add contact
//     2. Look up by name
//     3. Look up by phone (reverse lookup)
//     4. List by city
//     5. List all
//     6. Remove contact
//     7. Quit
//
//   Keep all three data structures in sync:
//   - When adding: insert into primary map, phone index, and city multimap
//   - When removing: erase from all three
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex03 ex03_phone_book.cpp

// YOUR CODE HERE
