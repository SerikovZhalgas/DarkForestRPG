#include "ItemDatabase.h"

namespace ItemDatabase
{
    const ItemDefinition smallPotion{
        ItemType::Potion,
        "Small Potion",
        50,
        10
    };

    const ItemDefinition healthPotion{
        ItemType::Potion,
        "Health Potion",
        100,
        25
    };

    const ItemDefinition ironSword{
        ItemType::Weapon,
        "Iron Sword",
        100,
        10
    };

    const ItemDefinition darkBlade{
        ItemType::Weapon,
        "Dark Blade",
        400,
        30
    };

    const ItemDefinition chainArmor{
        ItemType::Armor,
        "Chain Armor",
        150,
        10
    };
}