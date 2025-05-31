// Imports
#include <iostream>
#include <cctype>
#include <limits>

// Global Vars
double total;
bool running = true;

// Functions
double addFunction(double numberOne, double numberTwo) {
    total = numberOne + numberTwo;
    return total;
}

double subtractFunction(double numberOne, double numberTwo) {
    total = numberOne - numberTwo;
    return total;
}

double multiplyFunction(double numberOne, double numberTwo) {
    total = numberOne * numberTwo;
    return total;
}

double divideFunction(double numberOne, double numberTwo) {
    total = numberOne / numberTwo;
    return total;
}

int main() {

    // Local Vars
    double numberOne;
    double numberTwo;
    char op;
    char useAgain;

    // Main loop
    while(running) {

        std::cout << "Simple Calculator" << std::endl;
        std::cout << "-----------------" << std::endl;
    
        std::cout << "Enter first number: ";
        std::cin >> numberOne;

        while (std::cin.fail()) {
            std::cout << "Please only enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> numberOne;
        }

        while(true) {
            std::cout << "Enter an operator (+, -, *, /): ";
            std::cin >> op;
    
            if (op == '+' || op == '-' || op == '*' || op == '/'){
                break;
            }

            std::cout << "Invalid operator, please enter one of +, -, *, /\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter second number: ";
        std::cin >> numberTwo;
        
        while (!std::cin) {
            std::cout << "Please only enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> numberTwo;
        }
        
        switch(op) {
            case '+':
                addFunction(numberOne, numberTwo);
                break;
            case '-':
                subtractFunction(numberOne, numberTwo);
                break;
            case '*':
                multiplyFunction(numberOne, numberTwo);
                break;
            case '/':
                if (numberOne == 0 || numberTwo == 0) {
                    std::cout << "Error: division by zero\n";
                } else {
                    divideFunction(numberOne, numberTwo);
                }
                break;
            default:
                throw std::runtime_error("Error: invalid operator. ");
                break;
            }
    
        std::cout << "You entered: " << numberOne << " " << op << " " << numberTwo << std::endl;
    
        std::cout << "Result: " << total << std::endl;

        std::cout << "Do you want to use the calculator again? Enter Y or N: ";
        std::cin >> useAgain;
        useAgain = (char)tolower(useAgain);
        if (useAgain == 'y'){
            running = true;
        } else {
            running = false;
        }
    }

    return 0;
}
