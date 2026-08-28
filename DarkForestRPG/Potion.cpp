#include "Potion.h"
#include "Player.h"
#include <iostream>

Potion::Potion(std::string name, int amount, Rarity rarity)
	: Item(name, amount, rarity),
	healAmount(amount)
{
}

bool Potion::use(Player& player) {
	if (!player.heal(healAmount))
	{
		std::cout << "Potion has no effect.\n";
		return false;
	}

	std::cout << "Used " << name << "!\n";
	
	return true;
}

bool Potion::isConsumable() const {
	return true;
}