#pragma once
#include "GameState.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include <memory>
#include <iostream>
#include <vector>
#include <string>

class BattleState : public GameState {
private:
    Player& player;
    std::shared_ptr<Entity> enemy;
    Game& game;
    bool playerTurn = true;
    bool battleOver = false;
    std::vector<std::string> menuOptions = {"Attack", "Items", "Run"};
    int selectedOption = 0;
    void playerAttack();
    void enemyAttack();
    void printStatus();
public:
    BattleState(Player& p, std::shared_ptr<Entity> e, Game& g);

    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;
};
