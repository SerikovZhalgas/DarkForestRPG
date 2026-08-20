#pragma once

#include "Item.h"

class Potion : public Item {
private:
	int healAmount;

public:
	Potion(std::string name, int amount);

	void use() override;
};
