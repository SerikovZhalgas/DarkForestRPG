#pragma once

#include "Player.h"
#include "Goblin.h"
#include "Combat.h"

class Game {
private:
    Player player;
    Goblin enemy;
    Combat combat;

public:
    Game(const std::string& playerName, int age, int level);

    void run();

private:
    void showPlayerInfo() const;
    void showResult() const;
};