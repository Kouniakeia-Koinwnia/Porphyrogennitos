#ifndef MENU_H
#define MENU_H

//Global Variables
extern bool musicEnabled;

// The main menu in the start screen
void mainMenu(int selected);


//Main Menu, with which the game starts
void MenuComp();

//Menu Elements
void newGameSel(int selected);
void newGame();
void settings();
void credits();

//Settings Elements
void playMusic();
void stopMusic();

#endif 