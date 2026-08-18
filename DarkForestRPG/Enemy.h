#pragma once
#include "Character.h"
#include <string>

class Player;

class Enemy : public Character {
public:
	void attackPlayer(Player& player);

	Enemy(std::string enemyName);
};