#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <filesystem>

struct Contact {
    std::string Name;
    std::string Phone;
    std::string Email;
};

std::string contactFile = "contacts.txt";

void clearScreen(){
    std::cout << "\x1B[2J\x1B[H";
}

void addContact(std::vector<Contact>& contactBook){
    clearScreen();
    std::string fullName;
    std::string phoneNumber;
    std::string email;

    std::cout << "Enter full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Enter phone: ";
    std::getline(std::cin, phoneNumber);

    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    Contact newContact{fullName, phoneNumber, email};
    contactBook.push_back(newContact);
}

void deleteContact(std::vector<Contact>& contactBook){
    clearScreen();
    std::string nameInput;
    std::vector<size_t> matches;

    std::cout << "Enter name (or part of name) to delete: ";
    std::getline(std::cin, nameInput);

    for(size_t i = 0; i < contactBook.size(); ++i){
        if(contactBook[i].Name.find(nameInput) != std::string::npos){
            matches.push_back(i);
        }
    }

    if(matches.empty()) {
        std::cout << "No contacts found matching " << nameInput << ".\n";
        return;
    }

    if (matches.size() == 1){
        size_t idx = matches[0];

        std::string deletedName = contactBook[idx].Name;
        std::string deletedPhone = contactBook[idx].Phone;
        std::string deletedEmail = contactBook[idx].Email;

        contactBook.erase(contactBook.begin() + idx);
        std::cout << "Deleted: " << deletedName << " | " << deletedPhone << " | " << deletedEmail << "\n";
        return;
    } 

    std::cout << "Multiple Matches Found\n";
    for(size_t k = 0; k < matches.size(); ++k){
        const auto& c = contactBook[matches[k]];
        std::cout << (k+1) << ")" << c.Name << " | " << c.Phone << " | " << c.Email << "\n";
    }

    int choice = 0;
    while(true) {
        std::cout << "Enter the number to delete (1-" << matches.size() << "): ";
        if(std::cin >> choice && choice >= 1 && choice <= (int)matches.size()){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            size_t toRemove = matches[choice-1];
            contactBook.erase(contactBook.begin() + toRemove);
            break;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter the number to delete (1-" << matches.size() << "): ";
        }
    }
}

void listContact(std::vector<Contact>& contactBook){
    clearScreen();
    std::string name;

    if(contactBook.empty()){
        std::cout << "─────────────────────────────────────────────\n";
        std::cout << "No contacts in your address book.\n";
        std::cout << "─────────────────────────────────────────────\n";
        return;
    }else {
        std::cout << "─────────────────────────────────────────────\n";
        std::cout << " Name                 │ Phone      │ Email\n";
        std::cout << "─────────────────────────────────────────────\n";
        for(const auto& contacts : contactBook){
            std::cout << std::left << " " << std::setw(20) << contacts.Name << " │ " << std::setw(10) << contacts.Phone << " │ " << std::setw(24) << contacts.Email << "\n";
        }
        std::cout << "─────────────────────────────────────────────\n";
    }
}

std::vector<Contact> searchContact(const std::vector<Contact>& contactBook){
    clearScreen();
    std::string nameSearch;
    std::string phoneSearch;
    std::string emailSearch;
    int userSearchPick;
    std::vector<Contact> searchResults;

    std::cout << "Enter 1 for name search. \nEnter 2 for phone number search. \nEnter 3 for email search.\n";
    std::cout << "Choice: ";
    std::cin >> userSearchPick;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(userSearchPick){
        case 1:
            std::cout << "Enter name to search: ";
            std::getline(std::cin, nameSearch);
            std::copy_if(contactBook.begin(), contactBook.end(), std::back_inserter(searchResults), [&nameSearch](const Contact& c){return c.Name.find(nameSearch) != std::string::npos;});
            return searchResults;
        case 2:
            std::cout << "Enter phone number to search: ";
            std::getline(std::cin, phoneSearch);
            std::copy_if(contactBook.begin(), contactBook.end(), std::back_inserter(searchResults), [&phoneSearch](const Contact& c){return c.Phone.find(phoneSearch) != std::string::npos;});
            return searchResults;
        case 3:
            std::cout << "Enter email to search: ";
            std::getline(std::cin, emailSearch);
            std::copy_if(contactBook.begin(), contactBook.end(), std::back_inserter(searchResults), [&emailSearch](const Contact& c){return c.Email.find(emailSearch) != std::string::npos;});
            return searchResults;
        default:
            std::cout << "Invalid input. Please pick a number 1 - 3: ";
            return searchResults;
    }
}

void loadData(std::vector<Contact>& contactBook){
    namespace fs = std::filesystem;
    if(!fs::exists(contactFile)){
        std::ofstream out("contacts.txt");
        out.close();
    } else {
        std::ifstream in(contactFile);
        if(!in) {
            std::cerr << "Error: Could not open " << contactFile << "\n";
        }
        std::string line;
    
        while(std::getline(in, line)){
            size_t firstComma = line.find(',');
            size_t secondComma = line.find(',', firstComma + 1);
            
            if(firstComma == std::string::npos){
                std::cerr << "Skipping malformed line: " << line << "\n";
                continue;
            }
    
            if(secondComma == std::string::npos){
                std::cerr << "Skipping malformed line: " << line << "\n";
                continue;
            }
    
            size_t phoneStart = firstComma + 1;
            size_t phoneLength = secondComma- phoneStart;
            
            
            std::string name = line.substr(0, firstComma);
            std::string phone = line.substr(phoneStart, phoneLength);
            std::string email = line.substr(secondComma + 1);
    
            contactBook.push_back({name, phone, email});
        }
    }
}

bool saveAndQuit(const std::vector<Contact>& contactBook){
    std::ofstream out(contactFile);

    if(!out){
        std::cerr << "Error: Failed to open " << contactFile << " for writing!\n";
        return false;
    }

    for(const auto& contacts : contactBook){
        out << contacts.Name << "," << contacts.Phone << "," << contacts.Email << std::endl;
    }

    out.close();

    std::cout << "Goodbye.";
    return false;
}

void menu(){
    std::cout << "### Contact Manager ###\n";
    std::cout << "1) Add a contact\n";
    std::cout << "2) Delete a contact\n";
    std::cout << "3) List all contacts\n";
    std::cout << "4) Search by name\n";
    std::cout << "5) Save & quit\n";
    std::cout << "Enter choice (1-5): ";
}

int main(){
    std::cout << std::fixed << std::setprecision(2);
    int userChoice;
    bool running = true;
    std::vector<Contact> contactBook;
    loadData(contactBook);

    while (running) {

        menu();
        std::cin >> userChoice;

        switch (userChoice){
            case 1:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                addContact(contactBook);
                break;
            case 2:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                deleteContact(contactBook);
                break;
            case 3:
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                listContact(contactBook);
                break;
            case 4:
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::vector<Contact> foundContacts = searchContact(contactBook);

                    if(foundContacts.empty()){
                        std::cout << "No contacts in your address book.\n";
                    } else {
                        std::cout << "\n--- Search Results ---\n";
                        for(const auto& contacts : foundContacts){
                            std::cout << "Name: " << contacts.Name << "\n";
                            std::cout << "Phone Number: " << contacts.Phone << "\n";
                            std::cout << "Email: " << contacts.Email << "\n";
                            std::cout << "----------------------\n";
                        }
                    }
                    break;
                }
            case 5:
                running = saveAndQuit(contactBook);
                break;
            default:
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Invalid choice. Please enter a number from 1 to 5.\n";
        }
    }

    return 0;
}
