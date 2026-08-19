#pragma once
#include "Character.h"
#include <string>

class Player;

class Enemy : public Character {
public:
	Enemy(std::string enemyName);

	virtual void attackPlayer(Player& player);
};