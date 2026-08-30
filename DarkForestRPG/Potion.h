#pragma once

#include "Item.h"

class Player;

class Potion : public Item {
private:
	int healAmount;

public:
	Potion(
		std::string name,
		int itemValue, 
		int amount, 
		Rarity rarity
	);

	bool use(Player& player) override;
	bool isConsumable() const override;
};
