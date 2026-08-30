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
	double statusMultiplier;
	double valueMultiplier;
};

const RarityData& getRarityData(Rarity rarity);

const char* rarityToString(Rarity rarity);
double rarityStatusMultiplier(Rarity rarity);
double rarityValueMultiplier(Rarity rarity);