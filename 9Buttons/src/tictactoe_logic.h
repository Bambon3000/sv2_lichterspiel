#ifndef TICTACTOE_LOGIC_H
#define TICTACTOE_LOGIC_H

void initializeGame();
bool updateGame(int button);
char checkForWin();
void displayGameEnding(char winner);

#endif