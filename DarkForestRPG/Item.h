#pragma once

#include "Rarity.h"
#include <string>

class Player;

class Item {
protected:
	std::string name;
	int value;
	Rarity rarity;

public:
	Item(
		std::string itemName, 
		int itemValue,
		Rarity itemRarity
	);
	virtual ~Item() = default;

	const std::string& getName() const;
	int getValue() const;
	Rarity getRarity() const;

	virtual bool use(Player& player) = 0;
	virtual bool isConsumable() const = 0;
};