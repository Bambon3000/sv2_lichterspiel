#include <FastLED.h>

#ifndef LED_CONTROL_H
#define LED_CONTROL_H

void setLEDsYellow();
void setLEDsBlack();
void setupLEDs();
void setMenuLEDs();
void tttUpdateLEDs(const char board[3][3]);
void memSeqUpdateLEDWrong(int block);
void memSeqUpdateLEDCorrect(int block);
void colSeqUpdateLEDCorrect(int block, CRGB color);
void colorsUpdateLEDs();
void setLEDsColor(CRGB color);
void setButtonLEDs(const CRGB colors[9]);

#endif