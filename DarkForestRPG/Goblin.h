#pragma once

#include "Enemy.h"

class Goblin : public Enemy {
public:
	Goblin();

	void attackPlayer(Player& player) override;
};