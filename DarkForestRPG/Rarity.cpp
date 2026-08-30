#include "Rarity.h"

namespace
{
	const RarityData commonData{
		"Common",
		1.0,
		1.0
	};

	const RarityData rareData{
		"Rare",
		1.25,
		1.5
	};

	const RarityData epicData{
		"Epic",
		1.5,
		2.0
	};

	const RarityData legendaryData{
		"Legendary",
		2.0,
		3.0
	};
}

const RarityData& getRarityData(Rarity rarity)
{
	switch (rarity)
	{
	case Rarity::Common:
		return commonData;
	case Rarity::Rare:
		return rareData;
	case Rarity::Epic:
		return epicData;
	case Rarity::Legendary:
		return legendaryData;
	default:
		return commonData;
	}
}

const char* rarityToString(Rarity rarity)
{
	return getRarityData(rarity).name;
}

double rarityStatusMultiplier(Rarity rarity)
{
	return getRarityData(rarity).statusMultiplier;
}

double rarityValueMultiplier(Rarity rarity)
{
	return getRarityData(rarity).valueMultiplier;
}