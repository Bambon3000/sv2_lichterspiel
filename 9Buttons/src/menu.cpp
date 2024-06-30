#include <Arduino.h>
#include "menu.h"
#include "display.h"
#include "buttons.h"
#include "tictactoe_logic.h"

MenuItem currentSelection = MI_TICTACTOE;

void displayMenu()
{
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(3);
    tft.setTextColor(currentSelection == MI_TICTACTOE ? TFT_BLACK : TFT_LIGHTGREY);
    tft.setCursor(10, 20);
    tft.println(currentSelection == MI_TICTACTOE ? ">Tic Tac Toe" : "Tic Tac Toe");
    tft.setTextColor(currentSelection == MI_MEMSEQ ? TFT_BLACK : TFT_LIGHTGREY);
    tft.setCursor(10, 60);
    tft.println(currentSelection == MI_MEMSEQ ? ">Memory Sequence" : "Memory Sequence");
    tft.setTextColor(currentSelection == MI_COLSEQ ? TFT_BLACK : TFT_LIGHTGREY);
    tft.setCursor(10, 100);
    tft.println(currentSelection == MI_COLSEQ ? ">Color Sequence" : "Color Sequence");
    tft.setTextColor(currentSelection == MI_PSM ? TFT_BLACK : TFT_LIGHTGREY);
    tft.setCursor(10, 200);
    tft.println(currentSelection == MI_PSM ? ">Strom sparen" : "Strom sparen");
    drawUpArrow(290, 150, 30, TFT_DARKGREEN);
    drawCircle(290, 185, 12, TFT_RED);
    drawDownArrow(290, 220, 30, TFT_DARKGREEN);
}

int getSelection(int diff)
{
    int temp;
    temp = (currentSelection + diff) % (LENGTH - 1);
    if (temp < 0)
        temp += (LENGTH - 1);
    return temp;
}

int updateMenu(int button)
{
    int selectedMenuItem = MI_NONE;

    if (button == TOP_MIDDLE)
    { // Nach oben
        currentSelection = static_cast<MenuItem>(getSelection(-1));
        displayMenu();
    }
    else if (button == BOTTOM_MIDDLE)
    { // Nach unten
        currentSelection = static_cast<MenuItem>(getSelection(+1));
        displayMenu();
    }
    else if (button == MIDDLE_MIDDLE)
    { // Eingabe (in der Mitte)
        if (currentSelection == MI_TICTACTOE)
        {
            selectedMenuItem = MI_TICTACTOE;
        }
        else if (currentSelection == MI_MEMSEQ)
        {
            selectedMenuItem = MI_MEMSEQ;
        }
        else if (currentSelection == MI_COLSEQ)
        {
            selectedMenuItem = MI_COLSEQ;
        }
        else if (currentSelection == MI_PSM)
        {
            selectedMenuItem = MI_PSM;
        }
    }
    else
    {
        // Nichts
    }
    return selectedMenuItem;
}