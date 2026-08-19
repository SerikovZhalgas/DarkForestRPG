#include "Game.h"
#include <iostream>

Game::Game(const std::string& playerName, int age, int level)
	: player(playerName, age, level), 
	enemy(), 
	combat(player, enemy) 
{
}

void Game::run() {
	std::cout << "====================\n";
	std::cout << "     Dark Forest RPG\n";
	std::cout << "====================\n\n";

	showPlayerInfo();

	combat.start();

	showResult();
}

void Game::showPlayerInfo() const {
	std::cout << "Player: " << player.name << "\n";
	std::cout << "Age: " << player.age << "\n";

	if (player.level < 1) {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: BUG\n";
	}
	else if (player.level < 10) {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: Beginner\n";
	}
	else if (player.level < 50) {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: Experienced\n";
	}
	else {
		std::cout << "Level: " << player.level << "\n";
		std::cout << "Rank: Veteran\n";
	}
}

void Game::showResult() const {
	if(combat.hasEscaped())
    {
        std::cout << "You have escaped from the battle!\n";
    }
    else if (!enemy.isAlive())
    {
        std::cout << "You have defeated the " << enemy.name << "!\n";
    }
    else
    {
        std::cout << "You have been defeated by the " << enemy.name << "!\n";
    }

    std::cout << "\n\nHealth: " << player.getHealth() << "\n";
    std::cout << "Enemy Health: " << enemy.getHealth() << "\n";
    std::cout << "Stamina: " << player.getStamina() << "\n";
    std::cout << "Gold: " << player.getGold() << "\n";
    std::cout << "Attack: " << player.getAttack() << "\n";
    std::cout << "Defense: " << player.getDefense() << "\n";

    if (player.isAlive())
    {
        std::cout << player.name << ": Alive\n";
    }
    else
    {
        std::cout << player.name << ": Dead\n";
    }

    if (enemy.isAlive())
    {
        std::cout << enemy.name << ": Alive\n";
    }
    else
    {
        std::cout << enemy.name << ": Dead\n";
    }
}