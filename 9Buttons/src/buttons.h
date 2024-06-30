#ifndef BUTTONS_H
#define BUTTONS_H

enum Button
{
    NO_BUTTON,
    TOP_LEFT,
    TOP_MIDDLE,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_MIDDLE,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_MIDDLE,
    BOTTOM_RIGHT
};

extern int buttonPinArray[];

void setupButtons();
bool readButton(int i);
int pressedButton();
int waitForPressedButton();

#endif