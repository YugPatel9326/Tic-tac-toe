// for functions used by both regular and battle game modes
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

enum Archetype { NONE=0, PALADIN, ALCHEMIST };

void printBoard(const vector<char>& b) {
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "-----------\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "-----------\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n";
}

int checkWin(const vector<char>& b, char p1mark='X', char p2mark='O') {
    const int W[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for (int i = 0; i < 8; ++i) {
        int a = W[i][0], c = W[i][1], d = W[i][2]; 
        if (b[a] == b[c] && b[c] == b[d]) {
            if (b[a] == p1mark) return 1;
            if (b[a] == p2mark) return 2;
        }
    }
    return 0;
}

bool boardFull(const vector<char>& b) {
    for (char cell : b) {
        if (cell != 'X' && cell != 'O' &&
            !(cell >= 'A' && cell <= 'Z') &&
            !(cell >= 'a' && cell <= 'z') &&
            cell != '?' && cell != '!' && cell != '@' && cell != '*' &&
            cell != '~' && cell != '$' && cell != '%' && cell != '#' && cell != '&') {
            return false;
        }
    }
    return true;
}

bool isAllowedMarkChar(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) return true;
    const string extras = "?!@*~$%#&";
    for (char e : extras) if (ch == e) return true;
    return false;
}

int countMarksOnBoard(const vector<char>& board) {
    int count = 0;
    for (char c : board) {
        if (!(c >= '1' && c <= '9')) ++count;
    }
    return count;
}

bool isAdjacentIndex(int from, int to) {
    if (from < 1 || from > 9 || to < 1 || to > 9) return false;
    int r1 = (from-1) / 3, c1 = (from-1) % 3;
    int r2 = (to-1) / 3, c2 = (to-1) % 3;
    int dr = abs(r1 - r2), dc = abs(c1 - c2);
    if (dr <= 1 && dc <= 1 && !(dr==0 && dc==0)) return true;
    return false;
}

int askForIndex(const string& prompt) {
    while (true) {
        cout << prompt;
        string s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        bool onlyDigits = true;
        if (s.size() > 3) onlyDigits = false;
        else {
            for (char ch : s) if (ch < '0' || ch > '9') { onlyDigits = false; break; }
        }
        if (!onlyDigits) { cout << "Please enter a number 1-9.\n"; continue; }
        int idx = stoi(s);
        if (idx < 1 || idx > 9) { cout << "Index must be 1-9.\n"; continue; }
        return idx;
    }
}

Archetype askForArchetype(const string& prompt) {
    while (true) {
        cout << prompt << " (Paladin / Alchemist): ";
        string s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (auto &c : s) c = tolower(c);
        if (s == "paladin") return PALADIN;
        if (s == "alchemist") return ALCHEMIST;
        cout << "Invalid archetype. Try again.\n";
    }
}

char askForMark(const string& prompt, const vector<char>& taken) {
    while (true) {
        cout << prompt;
        string s;
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (s.size() != 1) {
            cout << "Please enter exactly one character.\n";
            continue;
        }
        char ch = s[0];
        if (!isAllowedMarkChar(ch)) {
            cout << "That character is not allowed. Try again.\n";
            continue;
        }
        bool used = false;
        for (char t : taken) if (t == ch) used = true;
        if (used) {
            cout << "Cannot choose same mark as opponent, please select another.\n";
            continue;
        }
        return ch;
    }
}
