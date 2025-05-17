#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>

struct AccountHistory {
    std::string action; 
    std::string amount;    
    std::string newBalance; 
    std::string note; 
};

class BankAccount {
private:
    double balance;
    std::vector<AccountHistory> history;

public:
    BankAccount(double initialBalance = 0.0) : balance(initialBalance) {
    }

    void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Deposit amount must be positive." << std::endl;
            return;
        }

        balance += amount;
        std::cout << "Deposit successful. New account balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;

        std::string fixedAmount = "+$" + formatCurrency(amount);
        std::string fixedBalance = "Balance: $" + formatCurrency(balance);

        history.push_back({"Deposit", fixedAmount, fixedBalance, ""});
    }

    void withdraw(double amount) {
        std::string note;
        std::string action = "Withdraw";
        std::string fixedAmount = "-$" + formatCurrency(amount);
        std::string currentBalanceStr = "Balance: $" + formatCurrency(balance); // Capture balance before change for failed attempts

        if (amount <= 0) {
            std::cout << "Withdrawal amount must be positive." << std::endl;
            note = "Failed: Invalid amount";
             history.push_back({action + " Attempt", fixedAmount, currentBalanceStr, note});
            return;
        }

        if (balance - amount < 0) {
            std::cout << "Withdrawal failed: insufficient funds." << std::endl;
            note = "Failed: insufficient funds";
            history.push_back({action + " Attempt", fixedAmount, currentBalanceStr, note});
        } else {
            balance -= amount;
            std::cout << "Withdrawal successful. New account balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
            note = "";
            std::string newFixedBalance = "Balance: $" + formatCurrency(balance);
            history.push_back({action, fixedAmount, newFixedBalance, note});
        }
    }

    double getBalance() const {
        return balance;
    }

    void displayTransactionHistory() const {
        std::cout << "\n--- Transaction History ---" << std::endl;
        if (history.empty()) {
            std::cout << "No transactions yet." << std::endl;
        } else {
            size_t maxActionLen = 10;
            size_t maxAmountLen = 8;
            size_t maxBalanceLen = 10;
            size_t maxNoteLen = 6;

            for (const auto& entry : history) {
                if (entry.action.length() > maxActionLen) maxActionLen = entry.action.length();
                if (entry.amount.length() > maxAmountLen) maxAmountLen = entry.amount.length();
                if (entry.newBalance.length() > maxBalanceLen) maxBalanceLen = entry.newBalance.length();
                if (entry.note.length() > maxNoteLen) maxNoteLen = entry.note.length();
            }
            maxActionLen +=2; 
            maxAmountLen +=2;
            maxBalanceLen +=2;
            maxNoteLen +=2;


            std::cout << std::left
                      << std::setw(maxActionLen) << "Action"
                      << std::setw(maxAmountLen) << "Amount"
                      << std::setw(maxBalanceLen) << "New Balance"
                      << std::setw(maxNoteLen) << "Note" << std::endl;
            std::cout << std::string(maxActionLen + maxAmountLen + maxBalanceLen + maxNoteLen -1 , '-') << std::endl;

            for (const auto& entry : history) {
                std::cout << std::left
                          << std::setw(maxActionLen) << entry.action
                          << std::setw(maxAmountLen) << entry.amount
                          << std::setw(maxBalanceLen) << entry.newBalance
                          << std::setw(maxNoteLen) << entry.note << std::endl;
            }
        }
        std::cout << "-------------------------" << std::endl;
    }

private:
    std::string formatCurrency(double value) const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << value;
        return oss.str();
    }
};

void menu() {
    std::cout << "\n### Choose Action ###" << std::endl;
    std::cout << "1) Deposit" << std::endl;
    std::cout << "2) Withdraw" << std::endl;
    std::cout << "3) Show balance" << std::endl;
    std::cout << "4) Show history" << std::endl;
    std::cout << "5) Exit" << std::endl;
    std::cout << "#####################" << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    BankAccount bank(100.00);

    bool running = true;
    int userChoice;
    double amount;

    while (running) {
        menu();

        std::cout << "Enter choice: ";
        std::cin >> userChoice;

        while (std::cin.fail() || userChoice < 1 || userChoice > 5) {
            std::cout << "Invalid input. Please enter a number from 1 to 5: ";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userChoice;
        }

        switch (userChoice) {
            case 1:
                std::cout << "Enter amount to deposit: $";
                std::cin >> amount;
                while (std::cin.fail()) {
                    std::cout << "Invalid amount. Please enter a numeric value: $";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> amount;
                }
                bank.deposit(amount);
                break;
            case 2:
                std::cout << "Enter amount to withdraw: $";
                std::cin >> amount;
                 while (std::cin.fail()) {
                    std::cout << "Invalid amount. Please enter a numeric value: $";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin >> amount;
                }
                bank.withdraw(amount);
                break;
            case 3:
                std::cout << "Current Balance: $" << bank.getBalance() << std::endl;
                break;
            case 4:
                bank.displayTransactionHistory();
                break;
            case 5:
                std::cout << "Exiting program. Thank you!" << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
