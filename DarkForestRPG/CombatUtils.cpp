#include "CombatUtils.h"
#include <random>
#include <iostream>

int calculateDamage(int attack, int defense) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, 10);

	int random_num = distrib(gen);

	int damage = attack - 5 + random_num - defense;

	if (damage < 0) {
		damage = 0;
	}

	return damage;
}

void printDamage(const int& damage) {
	std::cout << "Damage: " << damage << "\n";
}