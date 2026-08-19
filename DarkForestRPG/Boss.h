#pragma once
#include "Enemy.h"

class Boss : public Enemy 
{
public:
	Boss(std::string bossName);

	~Boss() override;

	void takeDamage(int damage) override;
	void attackPlayer(Player& player) override;
};