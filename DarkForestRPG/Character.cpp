#include "Character.h"
#include <iostream>

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
    }
    else
    {
        std::cout << name << " health: " << health << "\n";
    }
}

bool Character::isAlive() const
{
    return health > 0;
}