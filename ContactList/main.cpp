#include <iostream>
#include <string>
#include <vector>

struct Contact {
    std::string Name;
    std::string Phone;
    std::string Email;
};

void addContact(){
    
}

void deleteContact(){

}

void listContact(){

}

void searchContact(){

}

bool saveAndQuit(){

    return false;
}

void menu(){
    std::cout << "### Contact Manager ###";
    std::cout << "1) Add a contact";
    std::cout << "2) Delete a contact";
    std::cout << "3) List all contacts";
    std::cout << "4) Search by name";
    std::cout << "5) Save & quit";
    std::cout << "Enter choice (1-5): ";
}

int main(){
    int userChoice;
    bool running = true;
    std::vector<Contact> contactBook;

    while (running) {

        menu();

        std::cout << "Enter choice: ";
        std::cin >> userChoice;

        switch (userChoice){
            case 1:
                addContact();
                break;
            case 2:
                deleteContact();
                break;
            case 3:
                listContact();
                break;
            case 4:
                searchContact();
                break;
            case 5:
                running = saveAndQuit();
        }
    }
    
    return 0;
}
