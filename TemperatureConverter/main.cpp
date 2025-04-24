#include <iostream>
#include <cctype>
#include <limits>
#include <iomanip>

double celsiusToFahrenheit(double celsius){
    return (celsius * 1.8) + 32;
}

double fahrenheitToCelsius(double fahrenheit){
    return (fahrenheit - 32) / 1.8;
}

double celsiusToKelvin(double celsius) {
    return celsius + 273.15;
}

double kelvinToCelsius(double kelvin) {
    while (kelvin < 0) {
        std::cout << "Kelvin can't be negative. Enter K >= 0: ";
        std::cin >> kelvin;
    }

    return kelvin - 273.15;
}

double fahrenheitToKelvin(double fahrenheit) {
    return (fahrenheit + 459.67) * 5/9;
}

double kelvinToFahrenheit(double kelvin) {
    while (kelvin < 0) {
        std::cout << "Kelvin can’t be negative. Enter K >= 0: ";
        std::cin >> kelvin;
    }
    return 1.8 * (kelvin - 273.15) + 32;
}

void menu() {
    std::cout << "###Choose conversion###" << std::endl;
    std::cout << "1) C to F" << std::endl;
    std::cout << "2) F to C" << std::endl;
    std::cout << "3) C to K" << std::endl;
    std::cout << "4) K to C" << std::endl;
    std::cout << "5) F to K" << std::endl;
    std::cout << "6) K to F" << std::endl;
}

bool useProgramAgain(char useAgain) {
    while (useAgain != 'y' && useAgain != 'n') {
        std::cout << "Please only enter y or n. ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> useAgain;
    }

    if (useAgain == 'y') {
        return true;
    } else {
        return false;
    }
}

int main() {
    int userChoice;
    char useAgain;
    double userTemp;
    double newTemp;
    bool running = true;


    while(running){
        menu();
        std::cout << "Enter choice: ";
        std::cin >> userChoice;

        while (!(std::cin >> userChoice) || userChoice < 1 || userChoice > 6){
            std::cout << "Please only enter a number from 1 to 6: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userChoice;
        }
         
        std::cout << "Enter temperature: ";
        std::cin >> userTemp;

        while(!std::cin) {
            std::cout << "Please only enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userTemp;
        }

        std::cout << std::fixed << std::setprecision(2);

        switch(userChoice) {
            case 1:
                newTemp = celsiusToFahrenheit(userTemp);
                std::cout << "The conversion between celsius to fahrenheit is: " << newTemp << std::endl;
                break;
            case 2:
                newTemp = fahrenheitToCelsius(userTemp);
                std::cout << "The conversion from fahrenheit to celsius is: " << newTemp << std::endl;
                break;
            case 3:
                newTemp = celsiusToKelvin(userTemp);
                std::cout << "The conversion from celsius to kelvin is: " << newTemp << std::endl;
                break;
            case 4:
                newTemp = kelvinToCelsius(userTemp);
                std::cout << "The conversion from kelvin to celsius is: " << newTemp << std::endl;
                break;
            case 5:
                newTemp = fahrenheitToKelvin(userTemp);
                std::cout << "The conversion from fahrenheit to kelvin is: " << newTemp << std::endl;
                break;
            case 6:
                newTemp = kelvinToFahrenheit(userTemp);
                std:: cout << "The conversion from kelvin to fahrenheit is: " << newTemp << std::endl;
                break;
        }

        std::cout << "Run the converter again? (Y/N): ";
        std::cin >> useAgain;
        useAgain = std::tolower(useAgain);

        running = useProgramAgain(useAgain);

    }

    return 0;
}
