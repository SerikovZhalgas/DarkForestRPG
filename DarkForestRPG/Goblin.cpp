#include "Goblin.h"
#include "Player.h"
#include "CombatUtils.h"
#include <iostream>

Goblin::Goblin()
	: Enemy("Goblin")
{
	attackPower = 20;
	defense = 5;
}

void Goblin::attackPlayer(Player& player) {
	std::cout << name << " makes a quick attack!\n";

	int damage = calculateDamage(attackPower, player.getDefense());

	printDamage(damage);
	player.takeDamage(damage);
}