#include <Arduino.h>
#include <vector>
#include <FastLED.h>
#include "buttons.h"
#include "display.h"
#include "led_control.h"

void displayMemSeqLevel(int level)
{
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(5, 10);
    tft.setTextColor(TFT_DARKGREEN);
    tft.setTextSize(4);
    tft.print("Level: ");
    tft.print(level);
}

void displayMemSeqSequence (int level) {
    displayMemSeqLevel(level);
    tft.setCursor(0, 40);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(4);
    tft.println("Merke dir die");
    tft.print("Reihenfolge!");
}

void displayMemSeqPrompt (int level) {
    displayMemSeqLevel(level);
    tft.setCursor(0, 50);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(4);
    tft.println("Tippe auf die");
    tft.println("Buttons in");
    tft.println("der eben");
    tft.println("gezeigten");
    tft.println("Reihenfolge");
}

void displayMemSeqGameOver (int level) {
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(70, 5);
    tft.println("Game Over!");
    tft.setCursor(0, 35);
    tft.print("Du hast Level ");
    tft.println(level);
    tft.print("erreicht!");
}

void playMemSeq()
{
    setLEDsYellow();
    int level = 1;
    std::vector<int> sequence;
    randomSeed(analogRead(5));

    while (true)
    {
        int newBlock = random(1, 10);
        sequence.push_back(newBlock);

        displayMemSeqLevel(level);

        if (level == 1) {
            displayMemSeqSequence(level);
            delay(2000);
            displayCountDown();
        }

        for (int i = 0; i < int(sequence.size()); i++)
        {
            memSeqUpdateLEDCorrect(sequence[i]);
            delay(300);
        }

        displayMemSeqPrompt(level);

        for (int i = 0; i < int(sequence.size()); i++) {
            int userInput = waitForPressedButton();

            if (userInput != sequence[i]) {

                memSeqUpdateLEDWrong(userInput);
                sequence.clear();
                displayMemSeqGameOver(level);
                displayBackToMenu();
                waitForPressedButton();
                return;
            }

            memSeqUpdateLEDCorrect(userInput);
        }
    level++;
    delay(500);
    }
}