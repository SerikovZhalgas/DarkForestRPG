#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "Weapon.h"
#include "Armor.h"
#include "CombatUtils.h"
#include <iostream>
#include <utility>

Player::Player(std::string playerName, int playerAge, int playerLevel)
	: Character(playerName),
	age(playerAge),
	level(playerLevel)
{
}
Player::~Player() = default;
int Player::getStamina() const
{
	return stamina;
}
int Player::getGold() const
{
	return gold;
}
bool Player::isDefending() const
{
	return defending;
}
void Player::resetDefending() {
	defending = false;
}
void Player::startDefending() {
	defending = true;
}
void Player::attackEnemy(Enemy& enemy) {
	std::cout << "Player attacks " << enemy.name << "!\n";

	int damage = calculateDamage(
		getAttack(),
		enemy.getDefense()
	);

	printDamage(damage);
	enemy.takeDamage(damage);
}
bool Player::heal(int amount) {
	if (amount <= 0) {
		return false;
	}
	
	int oldHealth = health;

	health += amount;

	if (health > 100) {
		health = 100;
	}

	int healedAmount = health - oldHealth;

	std::cout << name
		<< " healed for " << healedAmount
		<< "HP! Health: " << health << "\n";

	return healedAmount > 0;
}
void Player::addItem(std::unique_ptr<Item> item) {
	inventory.push_back(std::move(item));
}
void Player::showInventory() const {
	std::cout << "\nInventory:\n";

	if (inventory.empty()) {
		std::cout << "Inventory is empty.\n";
		return;
	}

	for (std::size_t i=0; i<inventory.size(); ++i) 
	{
		std::cout << i + 1 << ". " 
				  << inventory[i]->getName() 
				  << " (" << inventory[i]->getValue() 
				  << " gold)\n";
	}
}
bool Player::useItem(int index)
{
	if (index <= 0 || index > static_cast<int>(inventory.size()))
	{
		std::cout << "Invalid item choice!\n";
		return false;
	}

	std::size_t itemIndex =
		static_cast<std::size_t>(index - 1);

	Item* item = inventory[itemIndex].get();

	if (auto* weapon = dynamic_cast<Weapon*>(item))
	{
		if (equipment.getWeapon())
		{
			std::cout << "You already have a weapon equipped.\n";
			return false;
		}

		std::unique_ptr<Weapon> weaponOwnership(
			static_cast<Weapon*>(inventory[itemIndex].release())
		);

		inventory.erase(inventory.begin() + itemIndex);

		return equipWeapon(std::move(weaponOwnership));
	}

	if (auto* armor = dynamic_cast<Armor*>(item))
	{
		if (equipment.getArmor())
		{
			std::cout << "You already have armor equipped.\n";
			return false;
		}

		std::unique_ptr<Armor> armorOwnership(
			static_cast<Armor*>(inventory[itemIndex].release())
		);

		inventory.erase(inventory.begin() + itemIndex);

		return equipArmor(std::move(armorOwnership));
	}

	if (!item->use(*this))
	{
		return false;
	}

	if (item->isConsumable())
	{
		inventory.erase(inventory.begin() + itemIndex);
	}

	return true;
}

void Player::addAttack(int amount) {
	attackPower += amount;
}

bool Player::equipWeapon(std::unique_ptr<Weapon> weapon)
{
	if (!weapon)
	{
		return false;
	}

	if (!weapon->use(*this))
	{
		return false;
	}

	if (!equipment.equipWeapon(std::move(weapon)))
	{
		return false;
	}

	return true;
}

bool Player::equipArmor(std::unique_ptr<Armor> armor)
{
	if (!armor)
	{
		return false;
	}

	if (!armor->use(*this))
	{
		return false;
	}

	if (!equipment.equipArmor(std::move(armor)))
	{
		return false;
	}

	return true;
}

int Player::getAttack() const
{
	return attackPower + equipment.getAttackBonus();
}

int Player::getDefense() const
{
	return defense + equipment.getDefenseBonus();
}

const Equipment& Player::getEquipment() const
{
	return equipment;
}

bool Player::unequipWeapon()
{
	auto weapon = equipment.takeWeapon();

	if (!weapon) {
		std::cout << "No weapon equipped.\n";
		return false;
	}

	inventory.push_back(std::move(weapon));

	std::cout << "Weapon unequipped and returned to invetory.\n";

	return true;
}

bool Player::unequipArmor()
{
	auto armor = equipment.takeArmor();

	if (!armor)
	{
		std::cout << "No armor equipped.\n";
		return false;
	}

	inventory.push_back(std::move(armor));

	std::cout << "Armor unequipped and returned to inventory.\n";

	return true;
}

void Player::showEquipment() const
{
	std::cout << "\n=== Equipment ===\n";

	if (equipment.getWeapon())
	{
		std::cout << "Weapon: "
			<< equipment.getWeapon()->getName()
			<< "\n";
	}
	else {
		std::cout << "Weapon: None\n";
	}

	if (equipment.getArmor())
	{
		std::cout << "Armor: "
			<< equipment.getArmor()->getName()
			<< "\n";
	}
	else
	{
		std::cout << "Armor: None\n";
	}
}