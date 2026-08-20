#include "Potion.h"
#include <iostream>

Potion::Potion(std::string name, int amount)
	: Item(name, amount),
	healAmount(amount) 
{
}

void Potion::use() {
	std::cout << "Used " << name 
			  << ". Restores " << healAmount 
		      << " health!\n";
}