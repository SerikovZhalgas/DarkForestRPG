#include "Game.h"
#include <iostream>

int main()
{
	std::string playerName;
	int age;
	int level;

    std::cout << "Enter your name: ";
    std::cin >> playerName;

	std::cout << "Enter your age: ";
	std::cin >> age;

	std::cout << "Enter your level: ";
	std::cin >> level;

	Game game(playerName, age, level);
	game.run();

	return 0;
}