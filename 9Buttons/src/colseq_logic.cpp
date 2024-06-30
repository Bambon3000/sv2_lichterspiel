#include <Arduino.h>
#include <vector>
#include <FastLED.h>
#include "buttons.h"
#include "display.h"
#include "led_control.h"
#include "colseq_logic.h"
#include <algorithm>
#include <iterator>

const CRGB colors[] = {
    CRGB::Red, CRGB::Green, CRGB::Blue,
    CRGB::Yellow, CRGB::Cyan, CRGB::LimeGreen,
    CRGB::OrangeRed, CRGB::Purple, CRGB::White};

void displayGameOver(int level)
{
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(70, 5);
    tft.println("Game Over!");
    tft.setCursor(0, 35);
    tft.print("Du hast level ");
    tft.println(level);
    tft.print("erreicht!");
}

void displayLevel(int level)
{
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(5, 10);
    tft.setTextColor(TFT_DARKGREEN);
    tft.setTextSize(4);
    tft.print("Level: ");
    tft.print(level);
}

void displaySequencePrompt()
{
    tft.setCursor(0, 40);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(4);
    tft.println("Merke dir die");
    tft.print("Farbfolge!");
}

void displayUserPrompt(int level)
{
    displayLevel(level);
    tft.setCursor(0, 50);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(3);
    tft.println("Merke dir zuerst");
    tft.println("alle Buttons in");
    tft.println("den eben");
    tft.println("gezeigten Farben.");
    tft.println("Tippe dann auf");
    tft.println("diese in der eben");
    tft.println("gezeigten");
    tft.println("Reihenfolge.");
}

void playColorSequence()
{
    int level = 1;
    std::vector<int> sequence;
    randomSeed(analogRead(5));

    while (true)
    {
        int newColorIndex = random(0, 9);
        sequence.push_back(newColorIndex);

        displayLevel(level);
        displaySequencePrompt();
        delay(2000);

        if(level == 1) {
            displayCountDown();
            displayLevel(level);
        }

        for (int i = 0; i < int(sequence.size()); i++)
        {
            setLEDsColor(colors[sequence[i]]);
            delay(1000);
            setLEDsBlack();
            delay(500);
        }

        CRGB buttonColors[9];
        for (int i = 0; i < 9; i++)
        {
            buttonColors[i] = colors[i];
        }
        std::random_shuffle(&buttonColors[0], &buttonColors[10]);

        setButtonLEDs(buttonColors);
        displayUserPrompt(level);

        for (int i = 0; i < int(sequence.size()); i++)
        {
            int userInput = waitForPressedButton();

            if (buttonColors[userInput - 1] != colors[sequence[i]])
            {
                setLEDsBlack();
                sequence.clear();
                displayGameOver(level);
                displayBackToMenu();
                waitForPressedButton();
                return;
            }

            colSeqUpdateLEDCorrect(userInput, buttonColors[userInput - 1]);
        }

        level++;
        delay(500);
    }
}