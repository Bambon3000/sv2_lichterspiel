#include <iostream>
#include <array>
#include <optional>
using namespace std;

// Typdefinition für ein Tic Tac Toe Feld
using Board = array<char, 9>;

// Funktion, um das Spielfeld zu zeichnen
void drawBoard(const Board& board) {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "-----------" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "-----------" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
}

// Funktion, um zu überprüfen, ob das Spiel gewonnen wurde
bool checkWin(const Board& board, char player) {
    const array<array<int, 3>, 8> wins = {{
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Horizontale Linien
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Vertikale Linien
        {0, 4, 8}, {2, 4, 6}             // Diagonale Linien
    }};

    for (const auto& row : wins) {
        if (board[row[0]] == player && board[row[1]] == player && board[row[2]] == player)
            return true;
    }
    return false;
}

// Funktion, um den Zug eines Spielers auszuführen
optional<int> makeMove(Board& board, char player) {
    int move;
    cout << "Spieler " << player << ", gib deine Bewegung ein (1-9): ";
    cin >> move;

    if (move < 1 || move > 9 || board[move - 1] != (move + '0')) {
        cout << "Ungültige Bewegung! Bitte versuche es erneut." << endl;
        return nullopt;
    }
    board[move - 1] = player;
    return move;
}

int main() {
    Board board {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool isPlayer1Turn = true;
    char playAgain;

    // Schleife, die das Spiel durchläuft
    while (true) {
        // Spielfeld zeichnen
        drawBoard(board);

        // Spielerbewegung
        char player = (isPlayer1Turn) ? 'X' : 'O';
        auto move = makeMove(board, player);
        if (!move) continue;

        // Überprüfen, ob das Spiel gewonnen wurde
        if (checkWin(board, player)) {
            drawBoard(board);
            cout << "Spieler " << player << " gewinnt!" << endl;
            break;
        }

        // Überprüfen, ob das Spiel unentschieden ist
        bool isBoardFull = true;
        for (char c : board) {
            if (c >= '1' && c <= '9') {
                isBoardFull = false;
                break;
            }
        }
        if (isBoardFull) {
            drawBoard(board);
            cout << "Unentschieden!" << endl;
            break;
        }

        // Spieler wechseln
        isPlayer1Turn = !isPlayer1Turn;
    }

    // Fragen, ob die Benutzer erneut spielen möchten
    cout << "Möchten Sie erneut spielen? (J/N): ";
    cin >> playAgain;
    if (playAgain == 'J' || playAgain == 'j') {
        // Wenn ja, das Spiel neu starten
        main();
    } else {
        // Andernfalls, das Programm beenden
        cout << "Auf Wiedersehen!" << endl;
    }

    return 0;
}
