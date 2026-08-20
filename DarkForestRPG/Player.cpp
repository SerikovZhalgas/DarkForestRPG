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
bool Player::heal() {
	if (stamina >= 20) {
		health += 25;
		stamina -= 20;
		if (health > 100) {
			health = 100;
		}
		std::cout << name
			<< " healed! Health: " << health
			<< ", Stamina: " << stamina << "\n";
		return true;
	}
	else {
		std::cout << name
			<< " does not have enough stamina to heal!\n";
		return false;
	}
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

	for (const auto& item : inventory) {
		std::cout << "- " 
				  << item->getName() 
				  << " (" << item->getValue() << " gold)\n";
	}
}