#pragma once

#include <string>

class Item {
protected:
	std::string name;
	int value;

public:
	Item(std::string itemName, int itemValue);

	virtual ~Item() = default;

	const std::string& getName() const;
	int getValue() const;

	virtual void use() = 0; // Pure virtual function to be implemented by derived classes
};