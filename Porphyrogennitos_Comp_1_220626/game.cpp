#include <iostream>
#include <windows.h>
#include <vector>
#include <conio.h>
#include "game.h"
#include "menu.h"

//GLOBAL VARIABLES

//Basic Character variables (name, race, sex)
std::string name = " ", race = " ", sex = " ";

//Progress Character Variables (level, health)
int level = 0, xp = 0, health = 0, totalHealth = 0, maxHealth = 0;
int nextLevel = 0, heal = 0;

//Foe's Variables
std::string foeNames[] = { "Konnik", "Bagatur", "Bagain", "Cuman Cavalry", "Sekachi", "Bojtsi", "Mongol Mercenary", "Tatar Mercenary", "Alan Skirmisher", "Mongol Skirmisher"};
int currentFoeName = 9;
std::string currentFoe = " ";
int foeHp = 0, foeXp = 0, foeLevel = 0;
int malakas = 0;

//From Menu to Game Logic
void startGame()
{
	system("cls");

	level = 1;
	xp = 0;
	nextLevel = 76;
	health = 100;
	totalHealth = health;
	maxHealth = totalHealth;

	//basic character creation
	std::cout << "Enter Character's name: ";
	std::cin >> name;

	std::cout << "Enter Character's race: ";
	std::cin >> race;

	std::cout << "Enter Character's sex: ";
	std::cin >> sex;

	//fun little loading
	std::cout << "Creating Character.\n";
	Sleep(600);
	system("cls");
	std::cout << "Creating Character..\n";
	Sleep(600);
	system("cls");
	std::cout << "Creating Character...\n";
	Sleep(600);
	system("cls");

	MovingMenu(); //that includes HUD and can choose what to do with your character

	system("pause");

}

void HUD()
{
	system("cls");
	std::cout << "Name: " << name << "		Health: " << totalHealth << "\nRace: " << race << "\nSex: " << sex << "\nLevel: " << level << "\nXp: " << xp << "\nXp to Level: " << nextLevel << std::endl;
}

void MovingMenu()
{
	int selected = 0;

	std::vector<std::string> moveItems
	{
		"Move forward",
		"Rest",
		"Exit to main menu"
	};

	while (true)
	{
		system("cls");
		HUD();
		std::cout << "Choose your next move: \n";

		for (int i = 0; i < moveItems.size(); i++)
		{
			if (i == selected)
			{
				std::cout << " > " << moveItems[i] << "\n\n";
			}
			else
			{
				std::cout << "   " << moveItems[i] << "\n\n";
			}
		}

		int key = _getch();

		if (key == 224)
		{
			key = _getch();

			if (key == 72)
			{
				selected--;
				if (selected < 0)
				{
					selected = 2;
				}
			}
			else if (key == 80)
			{
				selected++;
				if (selected > 2)
				{
					selected = 0;
				}
			}
		}
		else if (key == 13)
		{
			if (selected == 0)
			{
				MoveFWD(); //Player Moves forward and 50/50 chance of encounter
			}
			else if (selected == 1)
			{
				Rest(); //Rest and recover if you have received any damage
			}
			else if (selected == 2)
			{
				MenuComp(); // leaves MovingMenu and goes back to previous menu/function
				exit(0);
			}
		}
	}
}

void MoveFWD()
{
	int temp = rand() % 100 + 1;
	std::cout << "You begin to move forward...\n";

	if (temp >= 50)
	{
		//Encounter Foe
		CreateFoe();

		std::string tempName = foeNames[rand() % currentFoeName];
		std::cout << "A " << tempName << "! Prepare to fight\n";
		currentFoe = tempName;
		Sleep(1000);

		//Enter Combat Mechanics
		Combat();

		return;
	}
	
	std::cout << "You find nothing of interest\n";
	Sleep(600);
	MovingMenu();
}

void Rest()
{
	std::cout << "You want to set up camp and rest\n";
	Sleep(1000);

	if (totalHealth < maxHealth)
	{
		totalHealth += 10 * level;

		if (totalHealth > maxHealth)
		{
			totalHealth = maxHealth;
		}
		std::cout << "You healed by resting. Health is now " << totalHealth << std::endl;
	}
	else
	{
		std::cout << "You are already at full health\n";
	}
	
	Sleep(1000);
}

void CreateFoe()
{
	foeHp = 30; //Foe's base health
	foeLevel = (rand() % 3) * level;
	foeHp = (rand() % 4) * totalHealth;
	foeXp = foeHp;

	if (foeHp == 0)
	{
		CreateFoe();
	}

	if (foeLevel == 0)
	{
		CreateFoe();
	}

}

void Combat()
{
	int selected = 0;

	if (totalHealth >= 1 && foeHp >= 1)
	{
		std::cout << "\n";
		std::vector<std::string>combatItems
		{
			"Attack",
			"Block",
			"Flee"
		};

		std::cout << "\n";

		while (true)
		{
			system("cls");
			CombatHUD();
			std::cout << "Choose your next move: \n";

			for (int i = 0; i < combatItems.size(); i++)
			{
				if (i == selected)
				{
					std::cout << " > " << combatItems[i] << "\n\n";
				}
				else
				{
					std::cout << "   " << combatItems[i] << "\n\n";
				}
			}

			int key = _getch();

			if (key == 224)
			{
				key = _getch();

				if (key == 72)
				{
					selected--;
					if (selected < 0)
					{
						selected = 2;
					}
				}
				else if (key == 80)
				{
					selected++;
					if (selected > 2)
					{
						selected = 0;
					}
				}
			}
			else if (key == 13)
			{
				if (selected == 0)
				{
					Attack(); //Player chooses to attack opponent
				}
				else if (selected == 1)
				{
					Block(); //Player chooses to block incoming attack, 50/50 chance of blocking succesfully
				}
				else if (selected == 2)
				{
					Flee(); // 50/50 chnace of succesfully fleeing combat returning to moving menu
				}
			}
		}
	}
}

void CombatHUD()
{
	system("cls");
	std::cout << "Name: " << name << "		|		Foe Name: " << currentFoe << "\nHealth: " << totalHealth << "		|		Foe Health: " << foeHp << "\nLevel: " << level << "		|		Foe Level: " << foeLevel << std::endl;
}

//Combat Options: attack, block and flee and damage outputs
void Attack()
{
	int damage = getPlayerDamage();
	int enemyDamage = getFoeAttack();

	Sleep(1000);

	std::cout << "Attacking... You did " << damage << " to the " << currentFoe << std::endl;
	foeHp -= damage;

	if (foeHp <= 0)
	{
		foeHp = 0;
		std::cout << "You defeated the " << currentFoe << "!\n";
		Sleep(1000);
		MovingMenu();
		return;
	}

	Sleep(600);

	std::cout << "\nOpponent is attacking you...\n";
	totalHealth -= enemyDamage;

	if (totalHealth <= 0)
	{
		totalHealth = 0;
		std::cout << "You died.\n";
		Sleep(1000);
		return;
	}

	std::cout << "You suffered " << enemyDamage << " damage. Current HP: " << totalHealth << std::endl;

	Sleep(1000);

}

//Player damage
int getPlayerDamage()
{
	return 8 * level / 2;
}

//Opponnet's damage
int getFoeAttack()
{
	return 6 * foeLevel / 2;
}

void Block()
{
	int enemyDamage = getFoeAttack();
	int i = rand() % 100 + 1;

	if (i >= 50)
	{
		std::cout << "You blocked the incoming attack\n";
		Sleep(1000);
		Combat();
	}
	else
	{
		std::cout << "You failed to block the attack\n";
		totalHealth -= getFoeAttack();
		std::cout << "You were stabbed for " << enemyDamage << "current hp: " << totalHealth << std::endl;
		Sleep(1000);
		Combat();
	}
}

void Flee()
{
	int enemyDamage = getFoeAttack() + 10;
	std::cout << "You try to run\n";
	int x = rand() % 100 + 1;

	if (x >= 50)
	{
		std::cout << "You managed to flee from battle\n";
		Sleep(1000);
		MovingMenu();
	}
	else
	{
		std::cout << "You failed to flee from combat\n";
		totalHealth -= getFoeAttack() + 10;
		std::cout << "You suffered " << enemyDamage << " damage from your opponent\n";
		std::cout << "Your current health is: " << totalHealth << std::endl;
		Sleep(1000);
		Combat();
	}
}