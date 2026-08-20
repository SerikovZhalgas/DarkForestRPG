#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Combat.h"
#include <memory>
#include <random>

class Game {
private:
    Player player;
    std::unique_ptr<Enemy> enemy;
    std::unique_ptr<Combat> combat;

    std::mt19937 generator;

public:
    Game(const std::string& playerName, int age, int level);

    void run();

private:
    void createEnemy();
    void showPlayerInfo() const;
    void showResult() const;
};