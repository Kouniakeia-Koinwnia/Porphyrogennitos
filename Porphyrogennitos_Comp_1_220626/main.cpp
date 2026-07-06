#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <string> //for getline
#include "game.h"
#include "menu.h"
#include <SFML/Graphics.hpp>


int main()
{
	//Initial Character Stats
	level = 1;
	xp = 0;
	nextLevel = 76;
	health = 100;
	totalHealth = health;
	maxHealth = totalHealth;

	MenuComp();
	
	return 0;
}