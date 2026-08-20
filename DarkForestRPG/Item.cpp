#include "Item.h"

Item::Item(std::string itemName, int itemValue)
	: name(std::move(itemName)), 
	value(itemValue) 
{
}

const std::string& Item::getName() const {
	return name;
}

int Item::getValue() const {
	return value;
}