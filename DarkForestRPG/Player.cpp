#include "Player.h"
#include "Enemy.h"
#include "CombatUtils.h"
#include <iostream>

Player::Player(std::string playerName, int playerAge, int playerLevel)
	: Character(playerName),
	age(playerAge),
	level(playerLevel)
{
}
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
	int damage = calculateDamage(attack, enemy.getDefense());
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
