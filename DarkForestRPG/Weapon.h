#pragma once

#include "Item.h"

class Player;

class Weapon : public Item {
private:
	int attackBonus;
	bool equipped = false;

public:
	Weapon(const std::string& itemName, int itemValue, int bonus);

	bool use(Player& player) override;

	int getAttackBonus() const;
	bool isEquipped() const;
	bool isConsumable() const override;
};
