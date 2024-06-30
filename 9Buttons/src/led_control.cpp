#include <FastLED.h>
#include "led_control.h"

#define NUM_LEDS 27
#define LED_PIN 25

CRGB leds[NUM_LEDS];

void setLEDsYellow()
{
    for (int i = 0; i < 27; i++)
    {
        leds[i] = CRGB::Yellow;
    }
    FastLED.show();
}

void setLEDsBlack()
{
    for (int i = 0; i < 27; i++)
    {
        leds[i] = CRGB::Black;
    }
    FastLED.show();
}

void setupLEDs()
{
    FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(30);
    setLEDsBlack();
}

void setMenuLEDs()
{
    leds[3] = CRGB::Green;
    leds[4] = CRGB::Green;
    leds[5] = CRGB::Green;

    leds[12] = CRGB::Red;
    leds[13] = CRGB::Red;
    leds[14] = CRGB::Red;

    leds[21] = CRGB::Green;
    leds[22] = CRGB::Green;
    leds[23] = CRGB::Green;

    FastLED.show();
}

void tttUpdateLEDs(const char board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int ledIndex = (row * 3 + col) * 3;
            if (board[row][col] == 'R')
            {
                leds[ledIndex] = CRGB::Red;
                leds[ledIndex + 1] = CRGB::Red;
                leds[ledIndex + 2] = CRGB::Red;
            }
            else if (board[row][col] == 'B')
            {
                leds[ledIndex] = CRGB::Blue;
                leds[ledIndex + 1] = CRGB::Blue;
                leds[ledIndex + 2] = CRGB::Blue;
            }
            else
            {
                leds[ledIndex] = CRGB::Black;
                leds[ledIndex + 1] = CRGB::Black;
                leds[ledIndex + 2] = CRGB::Black;
            }
        }
    }
    FastLED.show();
}

void memSeqUpdateLEDCorrect(int block)
{
    setLEDsYellow();
    int ledIndex = (block - 1) * 3; // block fängt bei 1 an, der ledIndex aber bei 0, deswegen (block - 1)
    leds[ledIndex] = CRGB::Green;
    leds[ledIndex + 1] = CRGB::Green;
    leds[ledIndex + 2] = CRGB::Green;
    FastLED.show();
    delay(400);
    setLEDsYellow();
    FastLED.show();
}

void memSeqUpdateLEDWrong(int block)
{
    setLEDsYellow();
    int ledIndex = (block - 1) * 3; // block fängt bei 1 an, der ledIndex aber bei 0, deswegen (block - 1)
    leds[ledIndex] = CRGB::Red;
    leds[ledIndex + 1] = CRGB::Red;
    leds[ledIndex + 2] = CRGB::Red;
    FastLED.show();
}

void colSeqUpdateLEDCorrect(int block, CRGB color)
{
    setLEDsBlack();
    int ledIndex = (block - 1) * 3; // block fängt bei 1 an, der ledIndex aber bei 0, deswegen (block - 1)
    leds[ledIndex] = color;
    leds[ledIndex + 1] = color;
    leds[ledIndex + 2] = color;
    FastLED.show();
    delay(400);
    setLEDsBlack();
    FastLED.show();
}

void setLEDsColor(CRGB color)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = color;
    }
    FastLED.show();
}

void setButtonLEDs(const CRGB colors[9])
{
    for (int i = 0; i < 9; i++)
    {
        leds[i * 3] = colors[i];
        leds[i * 3 + 1] = colors[i];
        leds[i * 3 + 2] = colors[i];
    }
    FastLED.show();
}