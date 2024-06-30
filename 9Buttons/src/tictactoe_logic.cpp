#include <Arduino.h>
#include <FastLED.h>
#include "tictactoe_logic.h"
#include "buttons.h"
#include "display.h"
#include "led_control.h"

char board[3][3];
bool playerTurn = true; // true heißt Spieler Rot, false heißt Spieler Blau

void resetBoard()
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            board[row][col] = ' ';
        }
    }
    tttUpdateLEDs(board);
}

void tttUpdateDisplay(bool playerTurn)
{
    resetDisplay();
    tft.setTextSize(4);

    playerTurn ? tft.setCursor(28, 80): tft.setCursor(15, 80);
    tft.setTextColor(TFT_BLACK);
    tft.print("Spieler ");

    tft.setTextColor(playerTurn ? TFT_RED : TFT_BLUE);
    tft.println(playerTurn ? "ROT" : "BLAU");

    tft.setCursor(50, 120);
    tft.setTextColor(TFT_BLACK);
    tft.print("ist dran!");
}

void initializeGame()
{
    resetBoard();
    tft.setCursor(45, 100);
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(4);
    tft.setTextColor(TFT_BLACK);
    tft.println("TicTacToe");
    delay(1500);
    tttUpdateDisplay(playerTurn);
}

char checkForWin()
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ')
        {
            return char(board[row][0]);
        }
    }
    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ')
        {
            return char(board[0][col]);
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return char(board[0][0]);
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return char(board[0][2]);
    }
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == ' ')
            {
                return ' ';
            }
        }
    }
    return 'U';
}

void displayGameEnding(char winner)
{
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(3);
    if (winner == 'R' || winner == 'B')
    {
        tft.setTextSize(4);

        tft.setCursor(10, 20);
        tft.setTextColor(TFT_BLACK);
        tft.print("Spieler ");

        tft.setTextColor(winner == 'R' ? TFT_RED : TFT_BLUE);
        tft.print(winner == 'R' ? "ROT" : "BLAU");

        tft.setCursor(10, 45);
        tft.setTextColor(TFT_BLACK);
        tft.print("gewinnt!");
    }
    else
    {
        tft.setTextColor(TFT_DARKGREEN);
        tft.setTextSize(4);
        tft.setCursor(0, 50);
        tft.println("Unentschieden");
    }
}

bool updateGame(int button)
{
    bool buttonMatrix[3][3] = {
        {false, false, false},
        {false, false, false},
        {false, false, false}};

    switch (button)
    {
    case TOP_LEFT:
        buttonMatrix[0][0] = true;
        break;
    case TOP_MIDDLE:
        buttonMatrix[0][1] = true;
        break;
    case TOP_RIGHT:
        buttonMatrix[0][2] = true;
        break;
    case MIDDLE_LEFT:
        buttonMatrix[1][0] = true;
        break;
    case MIDDLE_MIDDLE:
        buttonMatrix[1][1] = true;
        break;
    case MIDDLE_RIGHT:
        buttonMatrix[1][2] = true;
        break;
    case BOTTOM_LEFT:
        buttonMatrix[2][0] = true;
        break;
    case BOTTOM_MIDDLE:
        buttonMatrix[2][1] = true;
        break;
    case BOTTOM_RIGHT:
        buttonMatrix[2][2] = true;
        break;
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (buttonMatrix[row][col] && board[row][col] == ' ')
            {
                board[row][col] = playerTurn ? 'R' : 'B';
                playerTurn = !playerTurn;
                tttUpdateDisplay(playerTurn);
                // updateDisplay(board);
                tttUpdateLEDs(board);
            }
        }
    }

    char winner = checkForWin();
    if (winner != ' ')
    {
        displayGameEnding(winner);
        displayBackToMenu();
        waitForPressedButton();
        setLEDsBlack();
        return true;
    }
    else
    {
        return false;
    }
}