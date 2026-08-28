#include "Item.h"

Item::Item(std::string itemName, int itemValue, Rarity itemRarity)
	: name(std::move(itemName)), 
	value(itemValue),
	rarity(itemRarity)
{
}

const std::string& Item::getName() const {
	return name;
}

int Item::getValue() const {
	return value;
}

Rarity Item::getRarity() const
{
	return rarity;
}