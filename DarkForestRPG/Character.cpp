#include "Character.h"
#include <iostream>
#include <utility>

Character::Character(std::string characterName)
    : name(characterName)
{
}

Character::~Character()
{
    std::cout << "Character destructor\n";
}

int Character::getHealth() const
{
    return health;
}

int Character::getMaxHealth() const
{
    return maxHealth;
}

int Character::getAttack() const
{
    return attackPower;
}

int Character::getDefense() const
{
    return defense;
}

void Character::takeDamage(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        health = 0;

        std::cout << name << " is dead!\n";

        if (onHealthChanged)
        {
			onHealthChanged(*this, health);
        }

        if (onDeath)
        {
			onDeath(*this);
        }
    }
    else
    {
        std::cout << name << " health: " << health << "\n";
        
        if (onHealthChanged)
        {
            onHealthChanged(*this, health);
        }
    }
}

bool Character::isAlive() const
{
    return health > 0;
}

void Character::setOnDeath(
    std::function<void(Character&)> callback
)
{
	onDeath = std::move(callback);
}

void Character::setOnHealthChanged(
	std::function<void(Character&, int)> callback
)
{
	onHealthChanged = std::move(callback);
}