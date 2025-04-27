#include <iostream>
#include <iomanip>
#include <limits>

class BankAccount {
    private:
        double balance;

    public:void deposit(double amount);
        BankAccount(double initalBalance = 0.0) : balance(initalBalance) {

        }

    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;

};

void BankAccount::deposit(double amount) {
    // Enter thy holy code here
}

bool BankAccount::withdraw(double amount) {
    // Enter thy sinful code here
}

double BankAccount::getBalance() const {

}

void menu() {
    std::cout << "###Choose Action###" << std::endl;
    std::cout << "1) Deposit" << std::endl;
    std::cout << "2) Withdraw" << std::endl;
    std::cout << "3) Show balance" << std::endl;
    std::cout << "4) Show history" << std::endl;
    std::cout << "5) Exit" << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    BankAccount myObj;

    bool running = true;
    int userChoice;

    while(running){

        menu();

        std::cout << "Enter choice: ";
        std::cin >> userChoice;

        while(userChoice < 1 || userChoice > 5){
            std::cout << "Please only enter a number from 1 to 6: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userChoice;
        }

        switch(userChoice){
            case(1):
                return 0;
                break;
            case(2):
                return 0;
                break;
            case(3):
                return 0;
                break;
            case(4):
                return 0;
                break;
            case(5):
                running = false;
        }
    }


    return 0;
}
