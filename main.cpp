#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printBoard(const vector<char>& b) {
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "-----------\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "-----------\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n";
}

bool isValidMove(const vector<char>& b, int move) {
    return move >= 1 && move <= 9 && b[move - 1] != 'X' && b[move - 1] != 'O';
}

int getPlayerMove(const vector<char>& board, char player) {
    while (true) {
        cout << "Player " << player << ", enter your move (1-9): ";
        string input;
        cin >> input;

        bool onlyDigits = true;
        if (input.size() > 3) {             
            onlyDigits = false;
        } else {
            for (char ch : input) {
                if (ch < '0' || ch > '9') {
                    onlyDigits = false;
                    break;
                }
            }
        }

        if (!onlyDigits) {
            cout << "You must enter a number between 1 and 9\n";
            continue;
        }

        int move = stoi(input);              
        if (!isValidMove(board, move)) {
            cout << "Your move is not valid. Please try again\n";
            continue;
        }
        return move;
    }
}

int checkWin(const vector<char>& b) {
    const int W[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, 
        {0,3,6}, {1,4,7}, {2,5,8}, 
        {0,4,8}, {2,4,6}           
    };
    for (int i = 0; i < 8; ++i) {
        int a = W[i][0], c = W[i][1], d = W[i][2];
        if (b[a] == b[c] && b[c] == b[d]) {
            return (b[a] == 'X') ? 1 : 2;
        }
    }
    return 0;
}

bool boardFull(const vector<char>& b) {
    for (char cell : b) {
        if (cell != 'X' && cell != 'O') return false;
    }
    return true;
}

int main() {
    vector<char> board(9);
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;

    char current = 'X';
    while (true) {
        printBoard(board);

        int move = getPlayerMove(board, current);
        board[move - 1] = current;

        int winner = checkWin(board);
        if (winner != 0) {
            printBoard(board);
            cout << "Player " << (winner == 1 ? 'X' : 'O') << " is the winner!\n";
            break;
        }
        if (boardFull(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }
        current = (current == 'X') ? 'O' : 'X';
    }

    return 0;
}
