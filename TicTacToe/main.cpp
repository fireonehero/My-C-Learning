#include <iostream>
#include <string>
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
    std::cout << "0 " << b[0][0] << "  | " << b[0][1] << " | " << b[0][2] << "\n";
    std::cout << "  ---+---+---\n";
    std::cout << "1 " << b[1][0] << "  | " << b[1][1] << " | " << b[1][2] << "\n";
    std::cout << "  ---+---+---\n";
    std::cout << "2 " << b[2][0] << "  | " << b[2][1] << " | " << b[2][2] << "\n";
}



int main() {
    int row, col;
    char board[3][3];
    bool running = true;
    
    char currentPlayer = 'X';
    initializeBoard(board);
    
    while(running) {
        drawBoard(board);
        std::cout << "Player " << currentPlayer << ", enter row and column: ";
        std::cin >> row >> col;
        if(0 <= row,col < 3 || board[row][col] == ' '){
            std::cout << "Error: Please enter a valid move. ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Player " << currentPlayer << ", enter row and column: ";
            std::cin >> row >> col;
        }


    }


    return 0;
}
