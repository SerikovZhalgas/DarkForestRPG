#include "ItemFactory.h"
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Rarity.h"
#include "ItemData.h"
#include "WeaponData.h"
#include "ArmorData.h"
#include "PotionData.h"

#include <vector>
#include <functional>

namespace
{
    const PotionData smallPotionData{
    "Small Potion",
        50,
        10
    };

    const PotionData healthPotionData{
        "Health Potion",
        100,
        25
    };

    const WeaponData ironSwordData{
        "Iron Sword",
        100,
        10
    };

    const ArmorData chainArmorData{
        "Chain Armor",
        150,
        10
    };

    const WeaponData darkBladeData{
        "Dark Blade",
        400,
        30
    };

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

    std::vector<LootEntry> lootTable =
    {
        {
            50,
            [](std::mt19937& generator)
            {
                Rarity rarity = getRandomRarity(generator);

                int healAmount =
                    static_cast<int>(
                        smallPotionData.baseHeal * 
                        rarityStatusMultiplier(rarity)
                    );

                int value =
                    static_cast<int>(
                        smallPotionData.baseValue *
                        rarityValueMultiplier(rarity)
                    );

                return std::make_unique<Potion>(
                    smallPotionData.name,
                    value,
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
                    static_cast<int>(
                        healthPotionData.baseHeal *
                        rarityStatusMultiplier(rarity)
                        );

                int value =
                    static_cast<int>(
                        healthPotionData.baseValue *
                        rarityValueMultiplier(rarity)
                    );

                return std::make_unique<Potion>(
                    healthPotionData.name,
                    value,
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
                    static_cast<int>(
                        ironSwordData.baseAttack * 
                        rarityStatusMultiplier(rarity)
                    );

                int value =
                    static_cast<int>(
                        ironSwordData.baseValue * 
                        rarityValueMultiplier(rarity)
                    );

                return std::make_unique<Weapon>(
                    ironSwordData.name,
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
                    static_cast<int>(
                        chainArmorData.baseDefense * 
                        rarityStatusMultiplier(rarity)
                    );

                int value =
                    static_cast<int>(
                        chainArmorData.baseValue * 
                        rarityValueMultiplier(rarity)
                    );

                return std::make_unique<Armor>(
                    chainArmorData.name,
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
                    static_cast<int>(
                        darkBladeData.baseAttack * 
                        rarityStatusMultiplier(rarity)
                    );

                int value =
                    static_cast<int>(
                        darkBladeData.baseValue * 
                        rarityValueMultiplier(rarity)
                    );

                return std::make_unique<Weapon>(
                    darkBladeData.name,
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