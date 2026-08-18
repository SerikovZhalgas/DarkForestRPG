#include "Combat.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

Combat::Combat(Player& combatPlayer, Enemy& combatEnemy)
	: player(combatPlayer),
	enemy(combatEnemy)
{
}

void Combat::start() {
	while (player.isAlive() && enemy.isAlive() && !isRunning) {
		showRoundInfo();

		int action = showMenu();

		bool actionProcessed = processAction(action);

		if (actionProcessed) {
			if (!isRunning && enemy.isAlive() && player.isAlive())
			{
				enemyTurn();
			}

			round++;
		}
	}
}

void Combat::showRoundInfo() {
	std::cout << "====================\n";
	std::cout << "\nRound: " << round << "\n";
	std::cout << "====================\n\n";
}

int Combat::showMenu() {
	int action;

	std::cout << "1. Attack\n";
	std::cout << "2. Defend\n";
	std::cout << "3. Heal\n";
	std::cout << "4. Run\n";
	std::cout << "Choose action: ";

	std::cin >> action;

	return action;
}

void Combat::enemyTurn()
{
	if (enemy.isAlive())
	{
		enemy.attackPlayer(player);
	}
}

bool Combat::processAction(int action)
{
	switch (action)
	{
	case 1:
		player.attackEnemy(enemy);
		return true;

	case 2:
		std::cout << "You are defending.\n";
		player.startDefending();
		return true;

	case 3:
		return player.heal();
	case 4:
		std::cout << "You escaped from the battle!\n";
		isRunning = true;
		return false;

	default:
		std::cout << "Invalid action!\n";
		return false;
	}
}

bool Combat::hasEscaped() const
{
	return isRunning;
}

const Enemy& Combat::getEnemy() const
{
	return enemy;
}