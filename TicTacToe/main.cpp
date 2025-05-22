#include <iostream>
#include <limits>
    
void initializeBoard(char b[3][3]){
    for (int r = 0; r < 3; ++r){
        for (int c = 0; c < 3; ++c){
            b[r][c] = ' ';
        }
    }
}

void drawBoard(char b[3][3]) {
    std::cout << "   0   1   2\n";
    std::cout << "0  " << b[0][0] << " | " << b[0][1] << " | " << b[0][2] << "\n";
    std::cout << "  ---+---+---\n";
    std::cout << "1  " << b[1][0] << " | " << b[1][1] << " | " << b[1][2] << "\n";
    std::cout << "  ---+---+---\n";
    std::cout << "2  " << b[2][0] << " | " << b[2][1] << " | " << b[2][2] << "\n";
}

bool checkWin(char b[3][3], char currentPlayer) {
    if(b[0][0] == currentPlayer && b[0][1] == currentPlayer && b[0][2] == currentPlayer){
        return true;
    } else if(b[1][0] == currentPlayer && b[1][1] == currentPlayer && b[1][2] == currentPlayer) {
        return true;
    } else if(b[2][0] == currentPlayer && b[2][1] == currentPlayer && b[2][2] == currentPlayer) {
        return true;
    } else if(b[0][0] == currentPlayer && b[1][0] == currentPlayer && b[2][0] == currentPlayer) {
        return true;
    } else if(b[0][1] == currentPlayer && b[1][1] == currentPlayer && b[2][1] == currentPlayer) {
        return true;
    } else if(b[0][2] == currentPlayer && b[1][2] == currentPlayer && b[2][2] == currentPlayer) {
        return true;
    } else if(b[0][0] == currentPlayer && b[1][1] == currentPlayer && b[2][2] == currentPlayer) {
        return true;
    } else if(b[0][2] == currentPlayer && b[1][1] == currentPlayer && b[2][0] == currentPlayer) {
        return true;
    }
    return false;
}

bool isDraw(char b[3][3]){
    for (int r = 0; r < 3; ++r){
        for (int c = 0; c < 3; ++c){
            if (b[r][c] == ' '){
                return false;
            }
        }
    }
    return true;
}

int main() {
    int row, col;
    char board[3][3];
    bool running = true;
    
    char currentPlayer = 'X';
    initializeBoard(board);
    
    while(running) {
        drawBoard(board);
        while (true) {
            std::cout << "Player " << currentPlayer << ", enter row and column: ";
            std::cin >> row >> col;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter two numbers (e.g. 1 2).\n";
                continue;
            }else if (row < 0 || row > 2 || col < 0 || col > 2) {
                std::cout << "Coordinates must be between 0 and 2.\n";
                continue;
            }else if (board[row][col] != ' ') {
                std::cout << "That spot is already taken.\n";
                continue;
            }
            break;
        }
        board[row][col] = currentPlayer;
        if(checkWin(board, currentPlayer)){
            drawBoard(board);
            std::cout << "Game Over! Player " << currentPlayer << " Wins!\n";
            running = false;
        }else if (isDraw(board)){
            drawBoard(board);
            std::cout << "Game Over! It's a draw!\n";
            running = false;
        }
        currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
    }

    return 0;
}
