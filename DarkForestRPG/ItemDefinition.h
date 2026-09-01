#pragma once

#include "Rarity.h"

enum class ItemType
{
	Potion,
	Weapon,
	Armor
};

struct ItemDefinition
{
	ItemType type;

	const char* name;

	int baseValue;

	int baseStat;
};