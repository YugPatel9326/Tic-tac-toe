#include <iostream>
#include <string>
#include <limits>
using namespace std;

void playRegularGame();
void playBattleGame();

int main() {
    while (true) {
        cout << "Welcome to Tic-Tac-Toe. Which mode would you like to play?\n"
        cout << "1) Regular Tic-Tac-Toe\n";
        cout << "2) Battle Tic-Tac-Toe\n";
        cout << "Choose 1 or 2: ";
        string choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice != "1" && choice != "2") {
            cout << "Invalid choice. Try again.\n";
            continue;
        }
        if (choice == "1") {
            playRegularGame();
        } else {
            playBattleGame();
        }

        while (true) {
            cout << "Play again? (y/n): ";
            string again;
            cin >> again;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (again == "y" || again == "Y") break; 
            if (again == "n" || again == "N") {
                cout << "Exiting...\n";
                return 0;
            }
            cout << "Please enter y or n.\n";
        }
    }
    return 0;
}
