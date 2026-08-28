#pragma once

#include <memory>
#include <random>

class Item;

class ItemFactory
{
public:
	static std::unique_ptr<Item> createRandomItem(
		std::mt19937& generator
	);
};