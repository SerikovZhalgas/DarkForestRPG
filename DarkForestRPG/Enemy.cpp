#include "Enemy.h"
#include "Player.h"
#include "CombatUtils.h"
#include <iostream>

Enemy::Enemy(std::string enemyName)
	: Character(enemyName)
{
}

void Enemy::attackPlayer(Player& player)
{
	std::cout << name << " attacks " << player.name << "!\n";

	bool defending = player.isDefending();

	int defense = defending 
		? player.getDefense() * 2 
		: player.getDefense();

	if (defending) {
		std::cout << player.name << " is defending!\n";
		player.resetDefending();
	}

	int damage = calculateDamage(attackPower, defense);

	printDamage(damage);
	player.takeDamage(damage);
}

int Enemy::getXPReward() const
{
	return xpReward;
}

int Enemy::getLootChance() const
{
	return lootChance;
}

int Enemy::getGoldReward() const
{
	return goldReward;
}

bool Enemy::rollLoot() const
{
	return false;
}