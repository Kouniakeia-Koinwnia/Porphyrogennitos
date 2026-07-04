#ifndef GAME_H
#define GAME_H

//Global Variables

//Character Variables
extern std::string name, race, sex;

//Progress Variables
extern int level, xp, health, totalHealth, maxHealth, nextLevel, heal;

//Foe Variables
extern std::string foeNames[];
extern int currentFoeName;
extern std::string currentFoe;
extern int foeHp, foeXp, foeLevel;


//From Menu to Game Logic
void startGame();

//HUD's
void HUD();
void CombatHUD();

//Movement
void MovingMenu();
void MoveFWD();
void Rest();

//Foe Creation
void CreateFoe();

//Combat
void Combat();
void Attack();
void Block();
void Flee();
int getPlayerDamage();
int getFoeAttack();

#endif 