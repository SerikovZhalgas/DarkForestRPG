#pragma once

#include <memory>

class Weapon;
class Armor;

class Equipment
{
private:
	std::unique_ptr<Weapon> weapon;
	std::unique_ptr<Armor> armor;

public:
	bool equipWeapon(std::unique_ptr<Weapon> newWeapon);
	bool equipArmor(std::unique_ptr<Armor> newArmor);

	const Weapon* getWeapon() const;
	const Armor* getArmor() const;

	int getAttackBonus() const;
	int getDefenseBonus() const;

	std::unique_ptr<Weapon> takeWeapon();
	std::unique_ptr<Armor> takeArmor();
};