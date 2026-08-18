#pragma once
#include "Character.h"

class Boss : public Character {
public:
	Boss(std::string bossName);

	~Boss() override;

	void takeDamage(int damage) override;
};