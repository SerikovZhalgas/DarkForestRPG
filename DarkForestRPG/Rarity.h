#pragma once

enum class Rarity
{
	Common,
	Rare,
	Epic,
	Legendary
};

struct RarityData
{
	const char* name;
	double statMultiplier;
	double valueMultiplier;
};

const RarityData& getRarityData(Rarity rarity);

const char* rarityToString(Rarity rarity);
double rarityStatMultiplier(Rarity rarity);
double rarityValueMultiplier(Rarity rarity);