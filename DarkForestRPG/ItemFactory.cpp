#include "ItemFactory.h"
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Rarity.h"

#include <vector>
#include <functional>

namespace
{
    struct LootEntry
    {
        int weight;
        std::function<std::unique_ptr<Item>(std::mt19937&)> create;
    };

    struct RarityEntry
    {
        int weight;
        Rarity rarity;
    };

    std::vector<RarityEntry> rarityTable =
    {
        {60, Rarity::Common},
        {25, Rarity::Rare},
        {10, Rarity::Epic},
        {5, Rarity::Legendary}
    };

    Rarity getRandomRarity(std::mt19937& generator)
    {
        int totalWeight = 0;

        for (const auto& entry : rarityTable)
        {
            totalWeight += entry.weight;
        }

        std::uniform_int_distribution<int> roll(
            1,
            totalWeight
        );

        int value = roll(generator);

        for (const auto& entry : rarityTable)
        {
            if (value <= entry.weight)
            {
                return entry.rarity;
            }

            value -= entry.weight;
        }

        return Rarity::Common;
    }

    double getRarityMultiplier(Rarity rarity)
    {
        switch (rarity)
        {
        case Rarity::Common:
            return 1.0;

        case Rarity::Rare:
            return 1.25;

        case Rarity::Epic:
            return 1.5;

        case Rarity::Legendary:
            return 2.0;

        default:
            return 1.0;
        }
    }

    std::vector<LootEntry> lootTable =
    {
        {
            50,
            [](std::mt19937& generator)
            {
                Rarity rarity = getRandomRarity(generator);

                int healAmount =
                    static_cast<int>(10 * getRarityMultiplier(rarity));

                return std::make_unique<Potion>(
                    "Small Potion",
                    healAmount,
                    rarity
                );
            }
        },

        {
            30,
            [](std::mt19937& generator)
            {
                Rarity rarity = getRandomRarity(generator);

                int healAmount =
                    static_cast<int>(25 * getRarityMultiplier(rarity));

                return std::make_unique<Potion>(
                    "Health Potion",
                    healAmount,
                    rarity
                );
            }
        },

        {
            10,
            [](std::mt19937& generator)
            {
                Rarity rarity = getRandomRarity(generator);

                int attackBonus =
                    static_cast<int>(10 * getRarityMultiplier(rarity));

                int value =
                    static_cast<int>(100 * getRarityMultiplier(rarity));

                return std::make_unique<Weapon>(
                    "Iron Sword",
                    value,
                    attackBonus,
                    rarity
                );
            }
        },

        {
            5,
            [](std::mt19937& generator)
            {
                Rarity rarity = getRandomRarity(generator);

                int defenseBonus =
                    static_cast<int>(10 * getRarityMultiplier(rarity));

                int value =
                    static_cast<int>(150 * getRarityMultiplier(rarity));

                return std::make_unique<Armor>(
                    "Chain Armor",
                    value,
                    defenseBonus,
                    rarity
                );
            }
        },

        {
            5,
            [](std::mt19937& generator)
            {
                Rarity rarity = getRandomRarity(generator);

                int attackBonus =
                    static_cast<int>(10 * getRarityMultiplier(rarity));

                int value =
                    static_cast<int>(100 * getRarityMultiplier(rarity));

                return std::make_unique<Weapon>(
                    "Dark Blade",
                    value,
                    attackBonus,
                    rarity
                );
            }
        }
    };
}

std::unique_ptr<Item> ItemFactory::createRandomItem(
	std::mt19937& generator
)
{
    int totalWeight = 0;

    for (const auto& entry : lootTable)
    {
        totalWeight += entry.weight;
    }

    std::uniform_int_distribution<int> roll(
        1,
        totalWeight
    );

    int value = roll(generator);

    for (const auto& entry : lootTable)
    {
        if (value <= entry.weight)
        {
            return entry.create(generator);
        }

        value -= entry.weight;
    }

    return nullptr;
}