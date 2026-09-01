#include "Game.h"
#include "Boss.h"
#include "Goblin.h"
#include "Enemy.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "ItemFactory.h"
#include <iostream>
#include <random>

Game::Game(const std::string& playerName, int age, int level)
    : player(playerName, age, level),
	generator(std::random_device{}())
{
    createEnemy();

	enemy->setOnHealthChanged(
		[this](Character& character, int newHealth)
		{
			if (newHealth <= 25)
			{
				std::cout
					<< character.name
					<< " is low on health!\n";
			}
		}
	);
}

void Game::run() {
	std::cout << "====================\n";
	std::cout << "     Dark Forest RPG\n";
	std::cout << "====================\n\n";
	
	showPlayerInfo();

	player.addItem(std::make_unique<Potion>("Health Potion", 20, 20, Rarity::Common));
	player.addItem(
		std::make_unique<Weapon>("Iron Sword", 10, 10, Rarity::Common)
	);
	player.addItem(
		std::make_unique<Weapon>("Steel Sword", 20, 10, Rarity::Epic)
	);
	player.addItem(
		std::make_unique<Armor>("Helmet", 50, 13, Rarity::Common)
	);
	player.addItem(
		std::make_unique<Armor>("Sweet Helmet", 100, 1, Rarity::Legendary)
	);
	player.showInventory();

	enemy->setOnDeath(
		[this](Character& deadCharacter) 
		{
			std::cout << "\nEvent: " 
					  << deadCharacter.name 
					  << " died!\n";
		}
	);

	combat->start();

	if (!combat->hasEscaped() && !enemy->isAlive())
	{
		giveRewards();
		generateLoot();
	}

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
	if(combat->hasEscaped())
    {
        std::cout << "You have escaped from the battle!\n";
    }
    else if (!enemy->isAlive())
    {
        std::cout << "You have defeated the " << enemy->name << "!\n";
    }
    else
    {
        std::cout << "You have been defeated by the " << enemy->name << "!\n";
    }

	player.showStats();

    if (player.isAlive())
    {
        std::cout << player.name << ": Alive\n";
    }
    else
    {
        std::cout << player.name << ": Dead\n";
    }

    if (enemy->isAlive())
    {
        std::cout << enemy->name << ": Alive\n";
    }
    else
    {
        std::cout << enemy->name << ": Dead\n";
    }
}

void Game::createEnemy() {
	std::uniform_int_distribution<int> dis(0, 2);

	int enemyType = dis(generator);

    switch (enemyType) {
	case 0:
		enemy = std::make_unique<Enemy>("Wolf");
		break;

	case 1:
		enemy = std::make_unique<Goblin>();
		break;

	case 2:
		enemy = std::make_unique<Boss>("Dragon");
		break;
    }

	combat = std::make_unique<Combat>(player, *enemy);
}

void Game::giveRewards()
{
	int xp = enemy->getXPReward();
	int gold = enemy->getGoldReward();

	std::cout << "\n=== Rewards ===\n";

	player.addXP(xp);
	player.addGold(gold);

	std::cout << "Gold +" << gold << "\n";
}

void Game::generateLoot()
{
	std::uniform_int_distribution<int> chance(1, 100);

	int roll = chance(generator);

	if (roll > enemy->getLootChance())
	{
		std::cout << "No loot dropped.\n";
		return;
	}

	auto item = ItemFactory::createRandomItem(generator);

	if (!item)
	{
		std::cout << "Loot generation falied.\n";
		return;
	}

	std::cout << "Loot: "
		<< item->getName()
		<< "!\n";

	player.addItem(std::move(item));
}