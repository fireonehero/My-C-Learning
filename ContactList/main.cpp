#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iomanip>

struct Contact {
    std::string Name;
    std::string Phone;
    std::string Email;
};

std::string contactFile = "contacts.txt";

void addContact(std::vector<Contact>& contactBook){
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
    std::string name;


}

void listContact(std::vector<Contact>& contactBook){
    std::string name;

    if(contactBook.empty()){
        std::cout << "No contacts in your address book.\n";
        return;
    }

    for(const auto& contacts : contactBook){
        std::cout << contacts.Name << "," << contacts.Phone << "," << contacts.Email << std::endl;
    }

}

std::vector<Contact> searchContact(const std::vector<Contact>& contactBook){
    std::string nameSearch;
    std::string phoneSearch;
    std::string emailSearch;
    int userSearchPick;
    std::vector<Contact> searchResults;

    std::cout << "Enter 1 for name search. \nEnter 2 for phone number search. \nEnter 3 for email search: ";
    std::cin >> userSearchPick;
    std::cin.ignore();

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


bool saveAndQuit(){

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
                running = saveAndQuit();
                break;
            default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Invalid choice. Please enter a number from 1 to 5.";

        }
    }

    return 0;
}
