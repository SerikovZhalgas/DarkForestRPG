#include "ItemFactory.h"
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"

#include <vector>

namespace
{
    std::vector<LootEntry> lootTable =
    {
        {
            50,
            []()
            {
                return std::make_unique<Potion>(
                    "Small Potion",
                    10
                );
            }
        },

        {
            30,
            []()
            {
                return std::make_unique<Potion>(
                    "Health Potion",
                    25
                );
            }
        },

        {
            10,
            []()
            {
                return std::make_unique<Weapon>(
                    "Iron Sword",
                    100,
                    10
                );
            }
        },

        {
            5,
            []()
            {
                return std::make_unique<Armor>(
                    "Chain Armor",
                    150,
                    10
                );
            }
        },

        {
            5,
            []()
            {
                return std::make_unique<Weapon>(
                    "Dark Blade",
                    400,
                    30
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
            return entry.create();
        }

        value -= entry.weight;
    }

    return nullptr;
}