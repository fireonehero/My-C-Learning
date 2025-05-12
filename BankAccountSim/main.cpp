#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct AccountHistory {
    std::string action;
    std::string amount;
    std::string newBalance;
    std::string note;
};

std::string accountFile = "accountfile.txt";

class BankAccount {
    private:
        double balance;
        std::vector<AccountHistory>& history;

    public:
        void deposit(double amount){
            std::string action = "Deposit";
            std::string note = "";

            balance = balance + amount;
            std::cout << "New account amount: $" << balance << std::endl;

            std::string fixedAmount = "+$" + std::to_string(amount);
            std::string fixedBalance = "Balance: $" + std::to_string(balance);

            history.push_back({action, fixedAmount, fixedBalance, note});
        }
        BankAccount(double initalBalance = 0.0) : balance(initalBalance) {}

        void withdraw(double amount){
            std::string action = "Withdraw";
            std::string note;


            if (balance - amount < 0){
                std::cout << "Failed: insufficient funds";
                note = "Failed: insufficient funds";
            } else {
                balance = balance - amount;
                std::cout << "New account balance: $" << balance << std::endl;
                note = "";
            }
            std::string fixedAmount = "-$" + std::to_string(amount);
            std::string fixedBalance = "Balance: $" + std::to_string(balance);

            history.push_back({action, fixedAmount, fixedBalance, note});
        }

        double getBalance() const {
            std::cout << "$";
            return balance;
        }

        void transactionHistory() {
            std::cout << "Transaction History\n-------------------" << std::endl;

        }
        void loadData(std::vector<AccountHistory>& history){
            std::ifstream in(accountFile);
            if (!in.is_open()){
                std::cerr << "Error: could not open " << accountFile << "\n";
                return;
            }

            std::string line;
            while(std::getline(in, line)){

            }
}

};

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
    BankAccount bank;
    bank.loadData("accountfile.txt");

    bool running = true;
    int userChoice;
    double amount;

    while(running){

        menu();

        std::cout << "Enter choice: ";
        std::cin >> userChoice;

        while(userChoice < 1 || userChoice > 5){
            std::cout << "Please only enter a number from 1 to 5: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userChoice;
        }

        switch(userChoice){
            case(1):
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                bank.deposit(amount);
                break;
            case(2):
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                bank.withdraw(amount);
                break;
            case(3):
                std::cout << "Current Balance: " << bank.getBalance() << std::endl;
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
