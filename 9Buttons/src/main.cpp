#include <Arduino.h>
#include "buttons.h"
#include "display.h"
#include "led_control.h"
#include "menu.h"
#include "tictactoe_logic.h"
#include "memseq_logic.h"
#include "colseq_logic.h"

#define S_SETUP_MENU 0 // Definitionen der States
#define S_MENU 1
#define S_TTT 2
#define S_MEMSEQ 3
#define S_COLSEQ 4
#define S_PSM 5 // Power Saving Mode

int gameState = S_SETUP_MENU;

void welcomeScreen()
{
    setLEDsBlack();
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(4);
    tft.setCursor(30, 100);
    tft.setTextColor(TFT_BLACK);
    tft.println("LuminoTouch");
}

void powerSavingModeScreen()
{
    tft.fillScreen(TFT_WHITE);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_BLACK);

    tft.println("In zehn Sekunden");
    tft.println("wechselt die");
    tft.println("Konsole in den");
    tft.println("Energiesparmodus.");
    tft.println("Tippen Sie auf");
    tft.println("einen beliebigen");
    tft.println("Button, um wieder");
    tft.println("in die");
    tft.println("Spielauswahl zu");
    tft.println("kommen.");

    delay(10000);
}

void powerSavingMode()
{
    tft.fillScreen(TFT_BLACK);
    setLEDsBlack();
}

void setup()
{
    setupButtons();
    setupLEDs();
    setupDisplay();
}

void loop()
{
    int tempPressedButton;
    int tempState;
    int button;
    bool gameFinished;

    switch (gameState)
    {
    case S_SETUP_MENU:
        welcomeScreen();
        delay(2500);
        displayMenu();
        gameState = S_MENU;
        break;

    case S_MENU:
        setMenuLEDs();
        tempPressedButton = pressedButton();       // Gedrückten Button erfassen
        tempState = updateMenu(tempPressedButton); // Menu-Logik (Welches Item wurde ausgewählt?)

        if (tempState == MI_TICTACTOE)
        {
            gameState = S_TTT;
            initializeGame();
        }
        else if (tempState == MI_MEMSEQ)
        {
            gameState = S_MEMSEQ;
        }
        else if (tempState == MI_COLSEQ)
        {
            gameState = S_COLSEQ;
        }
        else if (tempState == MI_PSM)
        {
            gameState = S_PSM;
        }
        break;

    case S_TTT:
        button = pressedButton();
        gameFinished = false;

        if (button > 0)
        {
            gameFinished = updateGame(button);
        }

        if (gameFinished)
        {
            gameState = S_SETUP_MENU;
        }
        break;

    case S_MEMSEQ:
        playMemSeq();
        gameState = S_SETUP_MENU;
        break;

    case S_COLSEQ:
        setLEDsBlack();
        playColorSequence();
        gameState = S_SETUP_MENU;
        break;

    case S_PSM:
        powerSavingModeScreen();
        powerSavingMode();
        waitForPressedButton();
        gameState = S_SETUP_MENU;
        break;
    }
}