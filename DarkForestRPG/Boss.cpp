#include "Boss.h"
#include "Player.h"
#include "CombatUtils.h"
#include <iostream>

Boss::Boss(std::string bossName)
	: Enemy(bossName)
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

void Boss::attackPlayer(Player& player) {
	std::cout << name << " uses a heavy attack on " << player.name << "!\n";

	bool defending = player.isDefending();

	int defense = defending
		? player.getDefense() * 2
		: player.getDefense();

	if (defending)
	{
		std::cout << player.name << " is defending!\n";
		player.resetDefending();
	}

	int damage = calculateDamage(
		attackPower + 10,
		defense
	);

	printDamage(damage);
	player.takeDamage(damage);
}