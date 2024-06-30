#include <MCUFRIEND_kbv.h>
#include "display.h"

MCUFRIEND_kbv tft;

void setupDisplay()
{
    uint16_t identifier = tft.readID();
    tft.begin(identifier);
    tft.setRotation(1);
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(10, 100);
}

void resetDisplay()
{
    tft.fillScreen(TFT_WHITE);
    tft.setCursor(10, 100);
}

void displayBackToMenu() {
    tft.setCursor(0, 100);
    tft.setTextSize(3);
    tft.setTextColor(TFT_BLACK);
    tft.println("Tippe auf einen");
    tft.println("beliebigen Knopf,");
    tft.println("um wieder in die");
    tft.println("Spielauswahl zu");
    tft.println("kommen");
}

void displayCountDown()
{
    tft.setCursor(0, 130);
    tft.setTextSize(4);
    tft.setTextColor(TFT_RED);
    tft.print("3...");
    delay(1000);
    tft.print("2...");
    delay(1000);
    tft.print("1...");
    delay(1000);
}

void drawUpArrow(int x, int y, int size, uint16_t color) {
    int halfSize = size / 2;
    tft.fillTriangle(x, y - halfSize, x - halfSize, y + halfSize, x + halfSize, y + halfSize, color);
}

void drawDownArrow(int x, int y, int size, uint16_t color) {
    int halfSize = size / 2;
    tft.fillTriangle(x, y + halfSize, x - halfSize, y - halfSize, x + halfSize, y - halfSize, color);
}

void drawCircle(int x, int y, int radius, uint16_t color) {
    tft.fillCircle(x, y, radius, color);
}