#pragma once
#include <string>

class Character {
protected:
	int health = 100;
	int maxHealth = 100;
	int attackPower = 25;
	int defense = 10;

public:
	std::string name;

	Character(std::string characterName);
	virtual ~Character();

	int getHealth() const;
	int getMaxHealth() const;
	virtual int getAttack() const;
	virtual int getDefense() const;

	virtual void takeDamage(int damage);

	bool isAlive() const;
};