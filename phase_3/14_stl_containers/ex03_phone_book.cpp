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
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>


struct Contact {
	std::string name;
	std::string phone;
	std::string email;
	std::string city;
};


void print_contact(const Contact& contact) {

	std::cout << contact.name << std::endl;
	std::cout << contact.phone << std::endl;
	std::cout << contact.email << std::endl;
	std::cout << contact.city << std::endl;
	std::cout << std::endl;

}


int main() {

	
	// Part A — Primary lookup by name:
	std::map<std::string, Contact> contacts;
	contacts["Alice Johnson"]  = {"Alice Johnson",  "555-0101", "alice@email.com",   "New York"};
	contacts["Bob Smith"]      = {"Bob Smith",      "555-0102", "bob@email.com",     "Chicago"};
	contacts["Carol Davis"]    = {"Carol Davis",    "555-0103", "carol@email.com",   "New York"};
	contacts["Dan Lee"]        = {"Dan Lee",        "555-0104", "dan@email.com",     "Austin"};
	contacts["Eve Martinez"]   = {"Eve Martinez",   "555-0105", "eve@email.com",     "Chicago"};
	contacts["Frank Wilson"]   = {"Frank Wilson",   "555-0106", "frank@email.com",   "Austin"};
	contacts["Grace Kim"]      = {"Grace Kim",      "555-0107", "grace@email.com",   "New York"};
	contacts["Henry Brown"]    = {"Henry Brown",    "555-0108", "henry@email.com",   "Denver"};

	std::set<std::string> cities;

	// Part B — Reverse lookup by phone:
	std::unordered_map<std::string, std::string> phone_lookup;
	for (auto &[name, info] : contacts) {
		phone_lookup[info.phone] = info.name;
		cities.insert(info.city);
	}

	// Part C — Group by city using multimap:
	std::multimap<std::string, std::string> city_map;
	for (auto &[name, info] : contacts) {
		city_map.insert({info.city, info.name});
	}

	
	for (auto &city : cities) {
		auto range = city_map.equal_range(city);
		std::cout << city << std::endl;
		for (auto it = range.first; it != range.second; ++it) {
			std::cout << it->second << " ";
		}
		std::cout << std::endl;
	}


	int cmd;
	bool quit = false;
	std::string input;
	std::string phone;
	std::string email;
	std::string city;


	std::cout << R"(1. Add contact
	2. Look up by name
	3. Look up by phone (reverse lookup)
	4. List by city
	5. List all
	6. Remove contact
	7. Quit)" << std::endl;


	while (!quit) {

		std::cin >> cmd;

		switch (cmd) {
		case 1:
			std::cout << "Enter a name: ";
			std::cin >> input;
			std::cout << "Enter a phone: ";
			std::cin >> phone;
			std::cout << "Enter a email: ";
			std::cin >> email;
			std::cout << "Enter a city: ";
			std::cin >> city;
			contacts[input]  = {input,  phone, email, city};
			break;
		case 2:
			std::cout << "Enter a name: ";
			std::cin >> input;
			print_contact(contacts[input]);
			break;
		case 3:
			std::cout << "Enter a phone number: ";
			std::cin >> input;
			std::cout << phone_lookup[input] << std::endl;
			break;
		case 4:
			{
				std::cout << "Enter a city: ";
				std::cin >> input;
				auto range = city_map.equal_range(input);
				for (auto it = range.first; it != range.second; ++it) {
					//std::cout << it->second << " ";
					print_contact(contacts[it->second]);
				}
			}
			break;
		case 5:
			for (auto &[name, contact]: contacts) {
				print_contact(contact);
			}
			break;
		case 6:
			std::cout << "Enter a name: ";
			std::cin >> input;
			contacts.erase(input);
			break;
		case 7:
			quit = true;
		}

	}
	

}