#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>

bool running = true;
bool start = true;
int attemptCount = 0;

int pickRandomWin() {
    srand(time(0));
    int correctNumber = rand() % 101;
    return correctNumber;
}

void playAgain () {
    char playAgain;

    while(true) {
        std::cout << "Do you want to play again? Enter Y or N: ";
        std::cin >> playAgain;
        playAgain = std::tolower(playAgain);

        if (playAgain == 'y' || playAgain == 'n'){
            break;
        }

        std::cout << "Please only say Y or N.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    
    if(playAgain == 'y') {
        running = true;
        start = true;
        attemptCount = 0;
        
    } else if(playAgain == 'n'){
        running = false;
    } 

}

int main() {
    int userGuess = 1;
    int correctNumber;

    while(running) {

        if (start == true){
            correctNumber = pickRandomWin();
            std::cout << "A random number between 1 and 100 has been picked. Guess the number-I will tell you higher or lower." << std::endl;
            start = false;
        }

        std::cout << "Type your guess: ";
        std::cin >> userGuess;
        while(!std::cin){
            std::cout << "Please only enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> userGuess;
        }

        if (userGuess < correctNumber) {
            std::cout << "Your guess is too low, try again. " << std::endl;;
            attemptCount += 1;
            std::cout << "Current attempt count: " << attemptCount << std::endl;
        } else if (userGuess > correctNumber) {
            std::cout << "Your guess is too high, try again. " << std::endl;
            attemptCount += 1;
            std::cout << "Current attempt count: " << attemptCount << std::endl;
        } else {
            std::cout << "You got it correct! You got it in " << attemptCount << " guesses!" << std::endl;
            playAgain();
        }
    }

    return 0;
}
