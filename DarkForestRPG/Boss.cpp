#include "Boss.h"
#include <iostream>

Boss::Boss(std::string bossName)
	: Character(bossName)
{
}

Boss::~Boss()
{
	std::cout << "Boss destructor\n";
}

void Boss::takeDamage(int damage) {
	std::cout << name << " blocks part of the damage!\n";

	int reducedDamage = damage / 2;

	health -= reducedDamage;

	if (health <= 0) {
		health = 0;
		std::cout << name << " is dead!\n";
	}
	else {
		std::cout << name << " health: " << health << "\n";
	}
}
