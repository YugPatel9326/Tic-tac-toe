// regular game mode
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void printBoard(const vector<char>& b);
int checkWin(const vector<char>& b, char p1mark, char p2mark);
bool boardFull(const vector<char>& b);

int getPlayerMoveRegular(const vector<char>& board, char player) {
    while (true) {
        cout << "Player " << player << ", enter your move (1-9): ";
        string input;
        cin >> input;
        cin.ignore(1000, '\n');

        bool onlyDigits = true;
        if (input.size() > 3) onlyDigits = false;
        else {
            for (char ch : input) {
                if (ch < '0' || ch > '9') { onlyDigits = false; break; }
            }
        }
        if (!onlyDigits) {
            cout << "Please enter a number between 1 and 9.\n";
            continue;
        }
        int move = stoi(input);
        if (move < 1 || move > 9) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        if (board[move-1] == 'X' || board[move-1] == 'O') {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        return move;
    }
}

void playRegularGame() {
    vector<char> board(9);
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;
    char current = 'X';
    while (true) {
        printBoard(board);
        int move = getPlayerMoveRegular(board, current);
        board[move-1] = current;
        int winner = checkWin(board, 'X', 'O');
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
}
