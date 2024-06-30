#include <Arduino.h>
#include "buttons.h"

int prevButtonState[10];
int buttonPinArray[] = {3, 42, 41, 38, 37, 34, 33, 30, 29, 26}; // NO_BUTTON braucht keinen Pin, deswegen der unbenutzte Pin 3

void setupButtons()
{
    for (int i = 1; i < 10; i++)
    {
        pinMode(buttonPinArray[i], INPUT_PULLUP);
        prevButtonState[i] = 0;
    }
}

bool readButton(int i)
{
    return digitalRead(buttonPinArray[i]) == LOW;
}

int pressedButton()
{
    int tempBS = 0;

    for (int i = 1; i < 10; i++)
    {
        if (readButton(i) == true && prevButtonState[i] == false)
        {
            tempBS = i;
        }
        prevButtonState[i] = readButton(i);
    }

    return tempBS;
}

int waitForPressedButton()
{
    int button = NO_BUTTON;
    
    while (button == NO_BUTTON)
    {
        button = pressedButton();
    }

    return button;
}