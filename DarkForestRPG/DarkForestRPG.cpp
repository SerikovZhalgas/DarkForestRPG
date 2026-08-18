// DarkForestRPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Combat.h"

int main()
{
	std::string playerName;

    std::cout << "Enter your name: ";
    std::cin >> playerName;

	int age;
	std::cout << "Enter your age: ";
	std::cin >> age;

	int level;
	std::cout << "Enter your level: ";
	std::cin >> level;

	Player player(playerName, age, level);
	Enemy wolf("Wolf");
	Combat combat(player, wolf);

	std::cout << "====================\n";
	std::cout << "     Dark Forest RPG\n";
	std::cout << "====================\n\n";
	std::cout << "Player: " << player.name << "\n";
	std::cout << "Age: " << player.age << "\n";
	if (player.level < 1) {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: BUG\n";
	} else if (player.level < 10) {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: Beginner\n";
	} else if (player.level < 50) {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: Experienced\n";
	} else {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: Veteran\n";
	}
	combat.start();
	if (combat.hasEscaped()) {
		std::cout << "You have escaped from the battle!\n";
	}else if (!combat.getEnemy().isAlive()) {
		std::cout << "You have defeated the " << combat.getEnemy().name << "!\n";
	}
	else {
		std::cout << "You have been defeated by the " << combat.getEnemy().name << "!\n";
	}
	std::cout << "\n\nHealth: " << player.getHealth() << "\n";
	std::cout << "Enemy Health: " << combat.getEnemy().getHealth() << "\n";
	std::cout << "Stamina: " << player.getStamina() << "\n";
	std::cout << "Gold: " << player.getGold() << "\n";
	std::cout << "Attack: " << player.getAttack() << "\n";
	std::cout << "Defense: " << player.getDefense() << "\n";
	if (player.isAlive()) {
		std::cout << player.name << ": Alive\n";
	}
	else {
		std::cout << player.name << ": Dead\n";
	}
	if (!combat.getEnemy().isAlive()) {
		std::cout << combat.getEnemy().name << ": Dead\n";
	}
	else {
		std::cout << combat.getEnemy().name << ": Alive\n";
	}

	return 0;
}