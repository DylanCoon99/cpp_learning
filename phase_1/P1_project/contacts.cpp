// Phase 1 Project: Contact Book
//
// Build a command-line contact management application.
// See README.md for full requirements.
//
// Compile: g++ -std=c++20 -Wall -Wextra -o contacts contacts.cpp

// YOUR CODE HERE
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cctype>



enum class Category { Personal = 1, Work, Family, Other };


std::string category_to_string(Category c) {
    switch (c) {
    case Category::Personal:
        return "Personal";
    case Category::Work:
        return "Work";
    case Category::Family:
        return "Family";
    case Category::Other:
        return "Other";
    }
}


struct Contact {
    static int next_id;
    int id;
    std::string first_name;
    std::string last_name;
    std::string phone;
    std::string email;
    Category category;


    // Constructor
    Contact(std::string fname, std::string lname, std::string phone, std::string email, Category category)
        : first_name(fname), last_name(lname), phone(phone), email(email), category(category) {
        id = next_id;
        ++next_id;
    }



    void print() const {
        int box_width = 36;

        std::cout << std::setw(box_width);
        std::cout << "ID: " << id << std::endl;
        std::cout << "┌────────────────────────────────────┐" << std::endl;
        std::cout << "│" << std::left << std::setw(box_width) << "Name: " +  first_name + " " + last_name << "│" << std::endl;
        std::cout << "│" << std::left << std::setw(box_width) << "Phone: " +  phone << "│" << std::endl;
        std::cout << "│" << std::left << std::setw(box_width) << "Email: " +  email << "│" << std::endl;
        std::cout << "│" << std::left << std::setw(box_width) << "Category: " +  category_to_string(category) << "│" << std::endl;
        std::cout << "└────────────────────────────────────┘" << std::endl;
        std::cout << std::endl;
    }


}; 

// initialize the contact count at 0
int Contact::next_id = 0;



Contact* get_contact(std::vector<Contact>& contacts, int id) {

    for (auto& c : contacts) {
        if (c.id == id) {
            return &c;
        }
    }

    return nullptr;
}





// Core operations
void add_contact(std::vector<Contact>& contacts) {

    std::string fname;
    std::string lname;
    std::string phone;
    std::string email;
    int category;

    // need to prompt the user for each field
    std::cout << "Enter first name: ";
    std::cin >> fname;
    std::cout << "Enter last name: ";
    std::cin >> lname;
    std::cout << "Enter phone: ";
    std::cin >> phone;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Select a category (1=Personal, 2=Work, 3=Family, 4=Other): ";
    std::cin >> category;
    std::cout << std::endl;

    Contact contact = Contact(fname, lname, phone, email, static_cast<Category>(category));

    contacts.push_back(contact);
}


void view_all(const std::vector<Contact>& contacts) {

    for (const auto& contact : contacts) {
        contact.print();
    }


}


// Helpers
bool is_match(std::string term, std::string fname, std::string lname, std::string email, std::string phone) {

    std::string match_term;
    std::string fname_lower;
    std::string lname_lower;
    std::string email_lower;
    std::string phone_lower;

    for (auto& c : term) { match_term += std::tolower(c); }
    for (auto& c : fname) { fname_lower += std::tolower(c); }
    for (auto& c : lname) { lname_lower += std::tolower(c); }
    for (auto& c : email) { email_lower += std::tolower(c); }
    for (auto& c : phone) { phone_lower += std::tolower(c); }



    return fname_lower.find(match_term) != std::string::npos || lname_lower.find(match_term) != std::string::npos || email_lower.find(match_term) != std::string::npos|| phone_lower.find(match_term) != std::string::npos;
}



void search_contacts(const std::vector<Contact>& contacts) {

    // prompt the user for a search term
    std::string term;
    std::cout << "Enter a search term: ";
    std::cin >> term;

    // needs to be case insensitive


    for (const auto& contact : contacts) {
        // for each contact -> search across fname, lname, email, and phone

        if (is_match(term, contact.first_name, contact.last_name, contact.email, contact.phone)) {
            contact.print();
        }
    }

}



void edit_contact(std::vector<Contact>& contacts) {

    // prompt for contact id
    int id;

    std::cout << "Enter Contact ID: ";
    std::cin >> id;

    Contact* contact = get_contact(contacts, id);

    if (contact) {

        std::string first_name;
        std::string last_name;
        std::string email;
        std::string phone;

        // for each value let the user type a new one
        std::cout << "First Name: ";
        std::cin >> first_name;
        first_name = (first_name == "") ? contact->first_name : first_name;
        contact->first_name = first_name;

        std::cout << "Last Name: ";
        std::cin >> last_name;
        last_name = (last_name == "") ? contact->last_name : last_name;
        contact->last_name = last_name;

        std::cout << "Email Name: ";
        std::cin >> email;
        email = (email == "") ? contact->email : email;
        contact->email = email;

        std::cout << "Phone Name: ";
        std::cin >> phone;
        phone = (phone == "") ? contact->phone : phone;
        contact->phone = phone;


    } else {
        std::cout << "User with id " << id << " does not exist!" << std::endl;
    }

}



void delete_contact(std::vector<Contact>& contacts) {

    int id;
    std::cout << "Enter Contact ID: ";
    std::cin >> id;

    // Find and erase by iterator:
    for (auto it = contacts.begin(); it != contacts.end(); ++it) {
        if (it->id == id) {
            contacts.erase(it);
            break;
        }
    }

}



void view_by_category(const std::vector<Contact>& contacts) {

    int category_num;
    std::cout << "Select a category (1=Personal, 2=Work, 3=Family, 4=Other): ";
    std::cin >> category_num;
    Category category = static_cast<Category>(category_num);
    int count = 0;

    for (auto& contact : contacts) {
        if (contact.category == category) {
            contact.print();
            ++count;
        }
    }

    std::cout << "Found " << count << " " << category_to_string(category) << " contacts." << std::endl;


}



void print_stats(const std::vector<Contact>& contacts) {
    int total = 0;
    int personal_count = 0;
    int work_count = 0;
    int family_count = 0;
    int other_count = 0;
    Category cat;

    for (auto& contact : contacts) {

        ++total;
        cat = contact.category;

        switch (cat) {
        case Category::Personal:
            ++personal_count;
            break;
        case Category::Work:
            ++work_count;
            break;
        case Category::Family:
            ++family_count;
            break;
        case Category::Other:
            ++other_count;
            break;
        }
    }


    // display total count, count per category. I am skipping the most common domain part because I don't care to do it.

    std::cout << "Total Contacts: " << total << std::endl;
    std::cout << "Personal: " << personal_count << std::endl;
    std::cout << "Work: " << work_count << std::endl;
    std::cout << "Family: " << family_count << std::endl;
    std::cout << "Other: " << other_count << std::endl;



}




// Lookup
Contact* find_by_id(std::vector<Contact>& contacts, int id) {

    for (auto& contact : contacts) {
        if (contact.id == id) {
            return &contact;
        }
    }

    return nullptr;

}


int main() {


	/*
    
    Task: Display this numbered menu and loop until the user quits

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


	*/
    std::vector<Contact> contacts;


    std::cout << R"(
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
    )" << std::endl;

    std::cout << std::endl;
    


    // main loop
    bool quit = false;
    int cmd;

    while (!quit) {

        std::cout << "Enter a number to make a selection: ";

        std::cin >> cmd;
        switch (cmd){
        case 1:
            // handle add contact
            add_contact(contacts);
            break;
        case 2:
            // handle view all contacts
            view_all(contacts);
            break;
        case 3:
            // handle search contacts
            search_contacts(contacts);
            break;
        case 4:
            // handle edit contact
            edit_contact(contacts);
            break;
        case 5:
            // handle delete contact
            delete_contact(contacts);
            break;
        case 6:
            // handle view by category
            view_by_category(contacts);
            break;
        case 7:
            // handle statistics
            print_stats(contacts);
            break;
        case 8:
            // handle export (print formatted)
            view_all(contacts);
            break;
        case 9:
            // handle quit
            quit = true;
            break;

        }


    }

    std::cout << "Done!" << std::endl;




}