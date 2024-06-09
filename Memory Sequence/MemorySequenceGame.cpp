#include <vector>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int SIZE = 9;
char board[SIZE][SIZE];
vector<pair<int, int> > sequence;
int currentRound = 0;
bool gameOver = false;

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // Escape-Sequenz zum Löschen des Bildschirms
}

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void displayBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void addRandomFieldToSequence() {
    int x = rand() % SIZE;
    int y = rand() % SIZE;
    sequence.push_back({x, y});
}

void displaySequence() {
    for (auto field : sequence) {
        int x = field.first;
        int y = field.second;
        board[x][y] = '*';
        clearScreen();
        displayBoard();
        usleep(500000);  // Pause für 0.5 Sekunden
        board[x][y] = '.';
        clearScreen();
        displayBoard();
        usleep(500000);  // Pause für 0.5 Sekunden
    }
}

bool checkPlayerInput() {
    for (int i = 0; i <= currentRound; i++) {
        int x, y;
        cout << "Enter coordinates for field " << i + 1 << " (row and column): ";
        cin >> x >> y;
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Invalid coordinates. Please enter values between 0 and " << SIZE-1 << "." << endl;
            return false;
        }
        if (x != sequence[i].first || y != sequence[i].second) {
            return false;
        }
    }
    return true;
}

void playGame() {
    while (!gameOver) {
        addRandomFieldToSequence();
        currentRound++;
        clearScreen();
        cout << "Untitled - Round " << currentRound << endl;
        displaySequence();
        if (!checkPlayerInput()) {
            gameOver = true;
            cout << "Game Over! You reached round " << currentRound << endl;
        }
    }
}

int main() {
    srand(time(0));
    initializeBoard();
    playGame();
    return 0;
}
