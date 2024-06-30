#ifndef MENU_H
#define MENU_H

enum MenuItem
{// MI = MenuItem
    MI_TICTACTOE,
    MI_MEMSEQ,
    MI_COLSEQ,
    MI_PSM,
    MI_NONE,
    LENGTH
};

extern MenuItem currentSelection;

void displayMenu();
int updateMenu(int button);

#endif