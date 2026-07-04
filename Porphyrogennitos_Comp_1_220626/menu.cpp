#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <mmsystem.h> // Windows Multimedia Library (for music in the background)
#pragma comment(lib, "winmm.lib") //the pragma comment links the required library
#include "menu.h"
#include "game.h"

bool musicEnabled = true; // Music starts enabled by default

// The main menu in the start screen
void mainMenu(int selected)
{
	system("cls");

	std::vector<std::string> menuItems =
	{
		"New Game",
		"Settings",
		"Credits",
		"Exit"
	};

	//Menu theme start
	std::cout << "===================================\n";
	std::cout << "          PORPHYROGENITUS\n";
	std::cout << "        The Age of Basil II\n";
	std::cout << "===================================\n\n";

	//Arrow blink while selecting a menu item
	for (int i = 0; i < menuItems.size(); i++)
	{
		if (i == selected)
		{
			std::cout << " > " << menuItems[i] << "\n\n";
		}
		else
		{
			std::cout << "   " << menuItems[i] << "\n\n";
		}
	}

	//Menu theme end
	std::cout << "===================================\n";
	std::cout << "Use UP/DOWN arrows and ENTER. \n";

}



//Complete main menu, with arrows and enter keys as selectors
void MenuComp()
{
	int selected = 0;
	
	while (true)
	{
		mainMenu(selected);
		int key = _getch();

		if (key == 224)
		{
			key = _getch();

			//UP
			if (key == 72)
			{
				selected--;
				if (selected < 0)
				{
					selected = 3;
				}
			}

			//DOWN
			else if (key == 80)
			{
				selected++;
				if (selected > 3)
				{
					selected = 0;
				}
			}


		}
		//ENTER
		else if (key == 13)
		{
			if (selected == 0)
			{
				newGame();
			}
			else if (selected == 1)
			{
				settings();
			}
			else if (selected == 2)
			{
				credits();
			}
			else if (selected == 3)
			{
				exit(0);
			}
		}
	}
}

//In New Game menu selection
void newGame()
{
	int selected = 0;

	while (true)
	{
		newGameSel(selected);

		int key = _getch();

		if (key == 224)
		{
			key = _getch();

			if (key == 72)
			{
				selected--;
				if (selected < 0)
				{
					selected = 1;
				}
			}
			else if (key == 80)
			{
				selected++;
				if (selected > 1)
				{
					selected = 0;
				}
			}
		}
		else if (key == 13)
		{
			if (selected == 0)
			{
				startGame(); //from game.cpp, the function that actually start the game
			}
			else if (selected == 1)
			{
				return;
			}
		}
	}
}

//Menu Elements
void newGameSel(int selected)
{
	system("cls");

	std::vector<std::string> newGameItems
	{
		"Create a new character",
		"Back to main menu"//in the future I am going to add play as Basil the II, and experimental gameplay
	};
	std::cout << "===================================\n";
	std::cout << "        IN HOC SIGNO VINCES        \n";
	std::cout << "===================================\n\n";

	for (int i = 0; i < newGameItems.size(); i++)
	{
		if (i == selected)
		{
			std::cout << " > " << newGameItems[i] << "\n\n";
		}
		else
		{
			std::cout << "   " << newGameItems[i] << "\n\n";
		}
	}
	std::cout << "===================================\n";
}

void credits()
{
	system("cls");

	//Same as the menu theme header
	std::cout << "===================================\n";
	std::cout << "              CREDITS              \n";
	std::cout << "===================================\n\n";

	std::cout << " Developers: Honorius et Arcadius  \n\n\n";

	//Menu theme end
	std::cout << "===================================\n";
	std::cout << "Press ENTER to return to Main Menu. \n";
	_getch();

}

void settings()
{
	int selected = 0;

	while (true)
	{
		system("cls");

		std::cout << "===================================\n";
		std::cout << "              SETTINGS              \n";
		std::cout << "===================================\n\n";

		if (selected == 0)
		{
			std::cout << " > ";
		}
		else
		{
			std::cout << "   ";
		}

		std::cout << "Background Music: " << (musicEnabled ? "ON" : "OFF") << "\n\n";

		if (selected == 1)
		{
			std::cout << " > ";
		}
		else
		{
			std::cout << "   ";
		}

		std::cout << "Back\n\n";

		int key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				selected--;
				if (selected < 0)
					selected = 1;
				break;

			case 80:
				selected++;
				if (selected > 1)
					selected = 0;
				break;
			}
		}
		else if (key == 13)
		{
			switch (selected)
			{
			case 0:
				musicEnabled = !musicEnabled; //Toggle ON/OFF
				if (musicEnabled)
				{
					playMusic();
				}
				else
				{
					stopMusic();
				}
				break;

			case 1:
				return;
			}
		}
		//Eventually I want to add difficulty adjustment

		std::cout << "===================================\n";
		std::cout << "Press ENTER to return to Main Menu. \n";
	}
}

//Settings Elements
void playMusic()
{
	if (musicEnabled)
	{
		PlaySound(TEXT("music.wav"), NULL, SND_ASYNC | SND_LOOP);
		//SND_ASYNC = play in the background
		//SND_LOOP = repeat indefinitely
	}
}

void stopMusic()
{
	PlaySound(NULL, 0, 0);
}