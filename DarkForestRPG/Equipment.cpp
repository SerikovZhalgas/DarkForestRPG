#include "Equipment.h"
#include "Weapon.h"
#include "Armor.h"
#include <iostream>

bool Equipment::equipWeapon(std::unique_ptr<Weapon> newWeapon) {
	if (!newWeapon) {
		return false;
	}

	if (weapon) {
		std::cout << "Weapon slot is already occupied.\n";
		return false;
	}

	weapon = std::move(newWeapon);

	return true;
}

bool Equipment::equipArmor(std::unique_ptr<Armor> newArmor) {
	if (!newArmor) {
		return false;
	}

	if (armor) {
		std::cout << "Armor slot is already occupied.\n";
		return false;
	}

	armor = std::move(newArmor);

	return true;
}

const Weapon* Equipment::getWeapon() const
{
	return weapon.get();
}

const Armor* Equipment::getArmor() const
{
	return armor.get();
}

int Equipment::getAttackBonus() const
{
	if (weapon)
	{
		return weapon->getAttackBonus();
	}

	return 0;
}

int Equipment::getDefenseBonus() const
{
	if (armor)
	{
		return armor->getDefenseBonus();
	}

	return 0;
}

std::unique_ptr<Weapon> Equipment::takeWeapon() {
		return std::move(weapon);
}

std::unique_ptr<Armor> Equipment::takeArmor()
{
	return std::move(armor);
}
