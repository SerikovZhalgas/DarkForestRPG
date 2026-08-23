#include "Player.h"
#include "Item.h"
#include "Enemy.h"
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

	int damage = calculateDamage(attackPower, enemy.getDefense());

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

	if (!inventory[itemIndex]->use(*this))
	{
		return false;
	}

	inventory.erase(inventory.begin() + itemIndex);

	return true;
}