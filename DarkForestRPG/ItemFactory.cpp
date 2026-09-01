#include "ItemFactory.h"
#include "Item.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Rarity.h"
#include "ItemDatabase.h"

#include <vector>

namespace
{
    struct LootEntry
    {
        int weight;
        const ItemDefinition* definition;
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
        {50, &ItemDatabase::smallPotion},
        {30, &ItemDatabase::healthPotion},
        {10, &ItemDatabase::ironSword},
        {5,  &ItemDatabase::chainArmor},
        {5,  &ItemDatabase::darkBlade}
    };

    int applyStatMultiplier(int baseValue, Rarity rarity)
    {
        return static_cast<int>(
            baseValue * rarityStatMultiplier(rarity)
            );
    }

    int applyValueMultiplier(int baseValue, Rarity rarity)
    {
        return static_cast<int>(
            baseValue * rarityValueMultiplier(rarity)
            );
    }

    std::unique_ptr<Item> createPotion(
        const ItemDefinition& definition,
        Rarity rarity
    )
    {
        int healAmount =
            applyStatMultiplier(
                definition.baseStat,
                rarity
            );

        int value =
            applyValueMultiplier(
                definition.baseValue,
                rarity
            );

        return std::make_unique<Potion>(
            definition.name,
            value,
            healAmount,
            rarity
        );
    }

    std::unique_ptr<Item> createWeapon(
        const ItemDefinition& definition,
        Rarity rarity
    )
    {
        int attackBonus =
            applyStatMultiplier(
                definition.baseStat,
                rarity
            );

        int value =
            applyValueMultiplier(
                definition.baseValue,
                rarity
            );

        return std::make_unique<Weapon>(
            definition.name,
            value,
            attackBonus,
            rarity
        );
    }

    std::unique_ptr<Item> createArmor(
        const ItemDefinition& definition,
        Rarity rarity
    )
    {
        int defenseBonus =
            applyStatMultiplier(
                definition.baseStat,
                rarity
            );

        int value =
            applyValueMultiplier(
                definition.baseValue,
                rarity
            );

        return std::make_unique<Armor>(
            definition.name,
            value,
            defenseBonus,
            rarity
        );
    }

    std::unique_ptr<Item> createItem(
        const ItemDefinition& definition,
        std::mt19937& generator
    )
    {
        Rarity rarity = getRandomRarity(generator);

        switch (definition.type)
        {
        case ItemType::Potion:
            return createPotion(definition, rarity);

        case ItemType::Weapon:
            return createWeapon(definition, rarity);

        case ItemType::Armor:
            return createArmor(definition, rarity);

        default:
            return nullptr;
        }
    }
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
            return createItem(*entry.definition, generator);
        }

        value -= entry.weight;
    }

    return nullptr;
}