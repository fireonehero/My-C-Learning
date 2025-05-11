#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <vector>

struct AccountHistory {
    std::string action;
    double amount;
    double newBalance;
}


std::string accountFile = "accountfile.txt";

void loadData(std::vector<double>& history){
    std::ifstream in(accountFile);
    if (!in.is_open()){
        std::cerr << "Error: could not open " << accountFile << "\n";
        return;
    }

    std::string line;
    while(std::getline(in, line)){

    }
}

/*
        auto commaPos = line.rfind(',');
        if (commaPos == std::string::npos) {
            std::cerr << "Skipping malformed line: " << line << "\n";
            continue;
        }

        auto rawName = line.substr(0, commaPos);
        auto rawScoreStr = line.substr(commaPos + 1);
        auto name = trim(rawName);
        auto scoreStr = trim(rawScoreStr);

        if (!name.empty() && name.front() == '"' && name.back() == '"') {
            name = name.substr(1, name.size() - 2);
        }

        name = trim(name);
        scoreStr = trim(scoreStr);

        try {
            double score = std::stod(scoreStr);
            roster.push_back({ name, score });
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid score for " << name << ": " << scoreStr << "\n";
        }
    }
}
*/



class BankAccount {
    private:
        double balance;

    public:void deposit(double amount){
        balance = balance + amount;
        std::cout << "New account amount: " << balance << std::endl;
    }
    BankAccount(double initalBalance = 0.0) : balance(initalBalance) {}

    bool withdraw(double amount){
        if (balance - amount < 0){
            std::cout << "Error: too little balance. ";
            return false;
        } else {
            balance = balance - amount;
            std::cout << "New account balance: " << balance << std::endl;
            return true;
        }
    }

    double getBalance() const {
        return balance;
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
    std::vector<AccountHistory> history;

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
                history.push_back();
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
