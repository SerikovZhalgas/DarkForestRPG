#pragma once

#include <string>
#include <functional>

class Character {
protected:
	int health = 100;
	int maxHealth = 100;
	int attackPower = 25;
	int defense = 10;
	std::function<void(Character&)> onDeath;
	std::function<void(Character&, int)> onHealthChanged;

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

	void setOnDeath(std::function<void(Character&)> callback);
	void setOnHealthChanged(std::function<void(Character&, int)> callback);
};