#pragma once
#include "Character.h"
#include <string>

class Enemy;

class Player : public Character {
private:
	int stamina = 80;
	int gold = 250;
	bool defending = false;

public:
	int age;
	int level;

	Player(std::string playerName, int playerAge, int playerLevel);

	int getStamina() const;
	int getGold() const;

	bool isDefending() const;
	void resetDefending();
	void startDefending();

	void attackEnemy(Enemy& enemy);
	bool heal();
};