#pragma once
#include <string>

class Character {
protected:
	int health = 100;
	int attack = 25;
	int defense = 10;

public:
	std::string name;

	Character(std::string characterName);
	virtual ~Character();

	int getHealth() const;
	int getAttack() const;
	int getDefense() const;

	virtual void takeDamage(int damage);

	bool isAlive() const;
};