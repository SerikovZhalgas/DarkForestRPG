#pragma once

#include <memory>
#include <random>
#include <string>
#include <functional>

class Item;

struct LootEntry
{
	int weight;
	std::function<std::unique_ptr<Item>()> create;
};

class ItemFactory
{
public:
	static std::unique_ptr<Item> createRandomItem(
		std::mt19937& generator
	);
};