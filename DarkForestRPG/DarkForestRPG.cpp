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

class Player;

class Enemy {
private:
	int health = 100;
	int attack = 25;
	int defense = 10;

public:
	std::string name;

	int getHealth() const
	{
		return health;
	}
	int getAttack() const
	{
		return attack;
	}
	int getDefense() const
	{
		return defense;
	}

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

	bool isAlive() const {
		return health > 0;
	}

	void attackPlayer(Player& player);

	Enemy(std::string enemyName)
		: name(enemyName)
	{
	}
};

class Player {
private:
	int health = 100;
	int stamina = 80;
	int gold = 250;
	int attack = 25;
	int defense = 15;
	bool defending = false;
public:
	std::string name;
	int age;
	int level;
	Player(std::string playerName, int playerAge, int playerLevel)
		: name(playerName),
		age(playerAge),
		level(playerLevel)
	{
	}
	int getHealth() const
	{
		return health;
	}
	int getStamina() const
	{
		return stamina;
	}
	int getGold() const
	{
		return gold;
	}
	int getAttack() const
	{
		return attack;
	}
	int getDefense() const
	{
		return defense;
	}
	bool isDefending() const
	{
		return defending;
	}
	bool isAlive() const {
		return health > 0;
	}
	void resetDefending() {
		defending = false;
	}
	void startDefending() {
		defending = true;
	}
	void attackEnemy(Enemy& enemy) {
		std::cout << "Player attacks " << enemy.name << "!\n";
		int damage = calculateDamage(attack, enemy.getDefense());
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
	bool heal() {
		if (stamina >= 20) {
			health += 25;
			stamina -= 20;
			if (health > 100) {
				health = 100;
			}
			std::cout << name 
				<< " healed! Health: " << health 
				<< ", Stamina: " << stamina << "\n";
			return true;
		}
		else {
			std::cout << name 
				<< " does not have enough stamina to heal!\n";
			return false;
		}
	}
};

void Enemy::attackPlayer(Player& player)
{
	std::cout << name << " attacks " << player.name << "!\n";
	int defense = player.isDefending() ? player.getDefense() * 2 : player.getDefense();
	if (player.isDefending()) {
		std::cout << player.name << " is defending!\n";
		player.resetDefending();
	}
	int damage = calculateDamage(attack, defense);
	printDamage(damage);
	player.takeDamage(damage);
}

struct Combat {
	Player& player;
	Enemy& enemy;

	int round = 1;
	bool isRunning = false;

	Combat(Player& combatPlayer, Enemy& combatEnemy)
		: player(combatPlayer), 
		enemy(combatEnemy)
	{
	}

	void start() {
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

	void showRoundInfo() {
		std::cout << "====================\n";
		std::cout << "\nRound: " << round << "\n";
		std::cout << "====================\n\n";
	}

	int showMenu() {
		int action;
		std::cout << "1. Attack\n";
		std::cout << "2. Defend\n";
		std::cout << "3. Heal\n";
		std::cout << "4. Run\n";
		std::cout << "Choose action: ";
		std::cin >> action;
		return action;
	}

	void enemyTurn()
	{
		if (enemy.isAlive())
		{
			enemy.attackPlayer(player);
		}
	}

	bool processAction(int action)
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
};

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
	if (combat.isRunning) {
		std::cout << "You have escaped from the battle!\n";
	}else if (!combat.enemy.isAlive()) {
		std::cout << "You have defeated the " << combat.enemy.name << "!\n";
	}
	else {
		std::cout << "You have been defeated by the " << combat.enemy.name << "!\n";
	}
	std::cout << "\n\nHealth: " << player.getHealth() << "\n";
	std::cout << "Enemy Health: " << combat.enemy.getHealth() << "\n";
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
	if (!combat.enemy.isAlive()) {
		std::cout << combat.enemy.name << ": Dead\n";
	}
	else {
		std::cout << combat.enemy.name << ": Alive\n";
	}

	return 0;
}