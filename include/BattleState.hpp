#pragma once
#include "GameState.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class BattleState : public GameState {
private:
    Player& player;
    std::shared_ptr<Entity> enemy;
    Game& game;
    bool playerTurn = true;
    bool battleOver = false;
    sf::RectangleShape enemyPlaceholder; ///REMOVE LATER

    sf::Font font;
    sf::Text playerText;
    sf::Text enemyText;
    sf::Text infoText;

    sf::RectangleShape bg;///REMOVE LATER
    sf::RectangleShape playerHPBar;///REMOVE LATER
    sf::RectangleShape enemyHPBar;///REMOVE LATER

    std::vector<std::string> menuOptions = {"Attack", "Items", "Run"};
    int selectedOption = 0;

public:
    BattleState(Player& p, std::shared_ptr<Entity> e, Game& g);//

    void handleInput(Game& game, sf::RenderWindow& window) override;
    void update(Game& game) override;
    void render(Game& game, sf::RenderWindow& window) override;
    void updateText();

private:
    void playerAttack();
    void enemyAttack();
    void setupText();
};
