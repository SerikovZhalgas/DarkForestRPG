#pragma once

#include <string>

class Player;

class Item {
protected:
	std::string name;
	int value;

public:
	Item(std::string itemName, int itemValue);
	virtual ~Item() = default;

	const std::string& getName() const;
	int getValue() const;

	virtual bool use(Player& player) = 0;
	virtual bool isConsumable() const = 0;
};