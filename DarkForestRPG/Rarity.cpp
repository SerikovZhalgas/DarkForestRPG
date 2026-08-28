#include "Rarity.h"

const char* rarityToString(Rarity rarity)
{
	switch (rarity)
	{	
	case Rarity::Common:
		return "Common";

	case Rarity::Rare:
		return "Rare";

	case Rarity::Epic:
		return "Epic";

	case Rarity::Legendary:
		return "Legendary";

	default:
		return "Unknown";
	}
}