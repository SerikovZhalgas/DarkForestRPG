#pragma once
#include "Character.h"
#include "Item.h"
#include "Equipment.h"

#include <string>
#include <vector>
#include <memory>

class Enemy;
class Weapon;
class Armor;

class Player : public Character {
private:
	int stamina = 80;
	int gold = 250;
	bool defending = false;

	std::vector<std::unique_ptr<Item>> inventory;
	Equipment equipment;

public:
	int age;
	int level;

	Player(std::string playerName, int playerAge, int playerLevel);
	~Player();

	int getStamina() const;
	int getGold() const;
	int getAttack() const override;
	int getDefense() const override;

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
	bool equipArmor(std::unique_ptr<Armor> armor);

	const Equipment& getEquipment() const;
	void showEquipment() const;

	bool unequipWeapon();
	bool unequipArmor();
};