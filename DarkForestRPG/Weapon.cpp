#include "Weapon.h"
#include "Player.h"
#include <iostream>

Weapon::Weapon(const std::string& itemName, int itemValue, int bonus, Rarity rarity)
	: Item(itemName, itemValue, rarity), 
	  attackBonus(bonus) 
{
}

bool Weapon::use(Player& player) {
	if (equipped) {
		std::cout << name << " is already equipped.\n";
		return false; // Indicate that the item was not used successfully
	}

	equipped = true;

	std::cout << "Equipped " << name 
			  << "! Attack +" << attackBonus << "\n";

	return true; // Indicate that the item was used successfully
}

bool Weapon::isConsumable() const
{
	return false;
}

bool Weapon::isEquipped() const
{
	return equipped;
}

int Weapon::getAttackBonus() const {
	return attackBonus;
}