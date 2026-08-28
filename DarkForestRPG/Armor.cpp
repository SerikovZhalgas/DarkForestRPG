#include "Armor.h"
#include "Player.h"
#include <iostream>

Armor::Armor(const std::string& itemName, int itemValue, int bonus, Rarity rarity)
	: Item(itemName, itemValue, rarity),
	defenseBonus(bonus)
{
}

bool Armor::use(Player& player) {
	std::cout << "Equipped " << name
		<< "! Defense + " << defenseBonus << "\n";

	return true;
}

bool Armor::isConsumable() const 
{
	return false;
}

int Armor::getDefenseBonus() const
{
	return defenseBonus;
}