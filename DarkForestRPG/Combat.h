#pragma once
#include "Player.h"
#include "Enemy.h"

class Combat {
private:
    Player& player;
    Enemy& enemy;

    int round = 1;
    bool isRunning = false;

public:
    Combat(Player& combatPlayer, Enemy& combatEnemy);

    void start();

    bool hasEscaped() const;
    const Enemy& getEnemy() const;

private:
    void showRoundInfo();
    int showMenu();
    void enemyTurn();
    bool processAction(int action);
};