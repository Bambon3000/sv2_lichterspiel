#ifndef DISPLAY_H
#define DISPLAY_H

#include <MCUFRIEND_kbv.h>

extern MCUFRIEND_kbv tft;

void setupDisplay();
void resetDisplay();
void displayBackToMenu();
void displayCountDown();
void drawUpArrow(int x, int y, int size, uint16_t color);
void drawDownArrow(int x, int y, int size, uint16_t color);
void drawCircle(int x, int y, int size, uint16_t color);

#endif