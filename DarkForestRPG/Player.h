#pragma once
#include "Character.h"
#include "Item.h"

#include <string>
#include <vector>
#include <memory>

class Enemy;

class Player : public Character {
private:
	int stamina = 80;
	int gold = 250;
	bool defending = false;

	std::vector<std::unique_ptr<Item>> inventory;

public:
	int age;
	int level;

	Player(std::string playerName, int playerAge, int playerLevel);
	~Player();

	int getStamina() const;
	int getGold() const;

	bool isDefending() const;
	void resetDefending();
	void startDefending();

	void attackEnemy(Enemy& enemy);
	bool heal();

	void addItem(std::unique_ptr<Item> item);
	void showInventory() const;
};