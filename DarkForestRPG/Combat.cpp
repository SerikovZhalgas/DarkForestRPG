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
	std::cout << "4. Use Item\n";
	std::cout << "5. Equipment\n";
	std::cout << "6. Run\n";
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
		return player.heal(25);
	
	case 4:
		useItem();
		return true;
	
	case 5:
		equipmentMenu();
		return false;

	case 6:
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

void Combat::useItem()
{
	player.showInventory();

	int index;

	std::cout << "Choose item (0 to cancel): ";
	std::cin >> index;

	if (index == 0)
	{
		std::cout << "You cancelled.\n";
		return;
	}

	player.useItem(index);
}

void Combat::equipmentMenu()
{
	player.showEquipment();

	int action;

	std::cout << "\n1. Unequip Weapon\n";
	std::cout << "2. Unequip Armor\n";
	std::cout << "0. Back\n";
	std::cout << "Choose action: ";

	std::cin >> action;

	switch (action)
	{
	case 1:
		player.unequipWeapon();
		break;

	case 2:
		player.unequipArmor();
		break;

	case 0:
		std::cout << "Back.\n";
		break;

	default:
		std::cout << "Invalid action!\n";
		break;
	}
}