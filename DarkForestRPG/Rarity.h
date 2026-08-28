#pragma once

enum class Rarity
{
	Common,
	Rare,
	Epic,
	Legendary
};

const char* rarityToString(Rarity rarity);