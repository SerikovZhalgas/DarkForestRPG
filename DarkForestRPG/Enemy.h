#pragma once
#include "Character.h"
#include <string>

class Player;

class Enemy : public Character {
private:
	int xpReward = 50;
	int goldReward = 25;
	int lootChance = 50;

public:
	Enemy(std::string enemyName);

	int getXPReward() const;
	int getGoldReward() const;
	int getLootChance() const;
	bool rollLoot() const;

	virtual void attackPlayer(Player& player);
};