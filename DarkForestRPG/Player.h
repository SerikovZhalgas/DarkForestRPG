#pragma once
#include "Character.h"
#include "Item.h"

#include <string>
#include <vector>
#include <memory>

class Enemy;
class Weapon;

class Player : public Character {
private:
	int stamina = 80;
	int gold = 250;
	bool defending = false;

	std::vector<std::unique_ptr<Item>> inventory;
	std::unique_ptr<Weapon> equippedWeapon;

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
	bool heal(int amount);

	void addItem(std::unique_ptr<Item> item);
	void showInventory() const;
	bool useItem(int index);
	void addAttack(int amount);
	bool equipWeapon(std::unique_ptr<Weapon> weapon);
	const Weapon* getEquippedWeapon() const;
};