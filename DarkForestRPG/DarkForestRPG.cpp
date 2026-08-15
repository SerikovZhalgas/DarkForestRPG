// DarkForestRPG.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <random>

int calculateDamage(int attack, int defense) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, 10);

	int random_num = distrib(gen);

	int damage = attack - 5 + random_num - defense;

	if (damage < 0) {
		damage = 0;
	}

	return damage;
}

void printDamage(const int& damage) {
	std::cout << "Damage: " << damage << "\n";
}

struct Player;

struct Enemy {
	std::string name;
	int health = 100;
	int attack = 25;
	int defense = 10;

	void takeDamage(int damage) {
		health -= damage;
		if (health <= 0) {
			health = 0;
			std::cout << name << " is dead!\n";
		}
		else {
			std::cout << name << " health: " << health << "\n";
		}
	}

	bool isAlive() {
		return health > 0;
	}

	void attackPlayer(Player& player);

	Enemy(std::string enemyName)
		: name(enemyName)
	{
	}
};

struct Player {
	std::string name;
	int age;
	int level;
	int health = 100;
	int stamina = 80;
	int gold = 250;
	int attack = 25;
	int defense = 15;
	bool isDefending = false;
	Player(std::string playerName, int playerAge, int playerLevel)
		: name(playerName),
		age(playerAge),
		level(playerLevel)
	{
	}
	bool isAlive() {
		return health > 0;
	}
	void attackEnemy(Enemy& enemy) {
		std::cout << "Player attacks " << enemy.name << "!\n";
		int damage = calculateDamage(attack, enemy.defense);
		printDamage(damage);
		enemy.takeDamage(damage);
	}
	void takeDamage(int damage) {
		health -= damage;
		if (health <= 0) {
			health = 0;
			std::cout << name << " is dead!\n";
		}
		else {
			std::cout << "Player health: " << health << "\n";
		}
	}
	void heal() {
		if (stamina >= 20) {
			health += 25;
			stamina -= 20;
			if (health > 100) {
				health = 100;
			}
			std::cout << name 
				<< " healed! Health: " << health 
				<< ", Stamina: " << stamina << "\n";
		}
		else {
			std::cout << name 
				<< " does not have enough stamina to heal!\n";
		}
	}
};

void Enemy::attackPlayer(Player& player)
{
	std::cout << name << " attacks " << player.name << "!\n";
	int defense = player.isDefending ? player.defense * 2 : player.defense;
	if (player.isDefending) {
		std::cout << player.name << " is defending!\n";
		player.isDefending = false;
	}
	int damage = calculateDamage(attack, defense);
	printDamage(damage);
	player.takeDamage(damage);
}

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

	int round = 1;
	bool isRunning = false;

	Player player(playerName, age, level);
	Enemy wolf("Wolf");

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
	while (player.isAlive() && wolf.isAlive()) {
		std::cout << "====================\n";
		std::cout << "\nRound: " << round << "\n";
		std::cout << "====================\n\n";

		int action;
		std::cout << "1. Attack\n";
		std::cout << "2. Defend\n";
		std::cout << "3. Heal\n";
		std::cout << "4. Run\n";
		std::cout << "Choose action: ";
		std::cin >> action;

		switch (action) 
		{
		case 1:
			player.attackEnemy(wolf);
			if (wolf.isAlive()) {
				wolf.attackPlayer(player);
			}
			round++;
			break;
		case 2:
			std::cout << "You are defending.\n";
			player.isDefending = true;
			if (wolf.isAlive()) {
				wolf.attackPlayer(player);
			}
			round++;
			break;
		case 3:
			player.heal();
			if (wolf.isAlive()) {
				wolf.attackPlayer(player);
			}
			round++;
			break;
		case 4:
			std::cout << "You are escaped!\n";
			return 0;
		default:
			std::cout << "Invalid action!\n";
			break;
		}
	}
	if (player.isAlive()) {
		std::cout << "You have defeated the " << wolf.name << "!\n";
	}
	else {
		std::cout << "You have been defeated by the " << wolf.name << "!\n";
	}
	std::cout << "\n\nHealth: " << player.health << "\n";
	std::cout << "Wolf Health: " << wolf.health << "\n";
	std::cout << "Stamina: " << player.stamina << "\n";
	std::cout << "Gold: " << player.gold << "\n";
	std::cout << "Attack: " << player.attack << "\n";
	std::cout << "Defense: " << player.defense << "\n";
	if (player.isAlive()) {
		std::cout << player.name << ": Alive\n";
	}
	else {
		std::cout << player.name << ": Dead\n";
	}
	if (!wolf.isAlive()) {
		std::cout << wolf.name << ": Dead\n";
	}
	else {
		std::cout << wolf.name << ": Alive\n";
	}

	return 0;
}