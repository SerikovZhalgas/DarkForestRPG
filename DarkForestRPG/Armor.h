#pragma once

#include "Item.h"

class Armor : public Item {
private:
	int defenseBonus;

public:
	Armor(const std::string& itemName, int itemValue, int bonus);

	bool use(Player& player) override;
	bool isConsumable() const override;

	int getDefenseBonus() const;
};