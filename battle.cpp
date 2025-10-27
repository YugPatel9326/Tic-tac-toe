// battle game mode
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Archetype { NONE=0, PALADIN, ALCHEMIST };

void printBoard(const vector<char>& b);
int checkWin(const vector<char>& b, char p1mark, char p2mark);
bool boardFull(const vector<char>& b);
int countMarksOnBoard(const vector<char>& board);
bool isAdjacentIndex(int from, int to);
int askForIndex(const string& prompt);
char askForMark(const string& prompt, const vector<char>& taken);
Archetype askForArchetype(const string& prompt);

bool isBattleCellEmpty(const vector<char>& board, int idx) {
    if (idx < 1 || idx > 9) return false;
    char c = board[idx-1];
    return (c >= '1' && c <= '9');
}

void playBattleGame() {
    vector<char> taken;
    char mark1 = askForMark("Player 1: choose your mark: ", taken);
    taken.push_back(mark1);
    char mark2 = askForMark("Player 2: choose your mark: ", taken);
    taken.push_back(mark2);

    Archetype arch1 = askForArchetype("Player 1 select your archetype");
    Archetype arch2 = askForArchetype("Player 2 select your archetype");

    vector<char> board(9);
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;

    char currentPlayerMark = mark1; 

    auto getArchForMark = [&](char m)->Archetype { return (m==mark1) ? arch1 : arch2; };

    while (true) {
        printBoard(board);
        cout << "Player (" << currentPlayerMark << ") - ";
        Archetype playerArch = getArchForMark(currentPlayerMark);
        cout << ((playerArch==PALADIN) ? "Paladin" : "Alchemist") << " - choose action:\n";
        cout << "  1) Regular move\n";
        cout << "  2) Special move\n";
        int choice;
        while (true) {
            choice = askForIndex("Enter 1 or 2: ");
            if (choice == 1 || choice == 2) break;
            cout << "Invalid, enter 1 or 2.\n";
        }

        bool actionTaken = false;
        if (choice == 1) {
            while (true) {
                int idx = askForIndex("Enter cell # 1-9 to place your mark: ");
                if (!isBattleCellEmpty(board, idx)) {
                    cout << "Cell is not empty. Try again.\n";
                    continue;
                }
                board[idx-1] = currentPlayerMark;
                actionTaken = true;
                break;
            }
        } else {
            if (playerArch == ALCHEMIST) {
                if (countMarksOnBoard(board) < 2) {
                    cout << "Not enough marks on board to swap.\n";
                } else {
                    int a = askForIndex("Enter index of first mark to swap: ");
                    int b = askForIndex("Enter index of second mark to swap: ");
                    if (a == b) {
                        cout << "Cannot pick the same cell twice.\n";
                    } else {
                        char ca = board[a-1], cb = board[b-1];
                        bool occA = !(ca >= '1' && ca <= '9');
                        bool occB = !(cb >= '1' && cb <= '9');
                        if (!occA || !occB) {
                            cout << "Both positions must contain marks to swap.\n";
                        } else if (ca == cb) {
                            cout << "Cannot swap two marks of the same type.\n";
                        } else {
                            board[a-1] = cb;
                            board[b-1] = ca;
                            actionTaken = true;
                        }
                    }
                }
            } else { //for Paladin
                if (countMarksOnBoard(board) < 1) {
                    cout << "No marks on board to shift.\n";
                } else {
                    int src = askForIndex("Enter index of mark to shift: ");
                    char sc = board[src-1];
                    if (sc >= '1' && sc <= '9') {
                        cout << "Selected cell is not occupied. Choose an occupied cell.\n";
                    } else {
                        int dst = askForIndex("Enter index of destination (must be adjacent and empty): ");
                        if (!isAdjacentIndex(src, dst)) {
                            cout << "Destination is not adjacent.\n";
                        } else {
                            if (!(board[dst-1] >= '1' && board[dst-1] <= '9')) {
                                cout << "Destination not empty.\n";
                            } else {
                                board[dst-1] = sc;
                                board[src-1] = '1' + (src-1);
                                actionTaken = true;
                            }
                        }
                    }
                }
            }
        }
        if (!actionTaken) {
            cout << "Invalid action. Please try again.\n";
            continue; 
        }
        int winner = checkWin(board, mark1, mark2);
        if (winner != 0) {
            printBoard(board);
            cout << "Player " << (winner == 1 ? mark1 : mark2) << " is the winner!\n";
            break;
        }
        if (boardFull(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }

        currentPlayerMark = (currentPlayerMark == mark1) ? mark2 : mark1;
    }
}
