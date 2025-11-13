#pragma once
#include "GameState.hpp"
#include "Player.hpp"
#include "Map.hpp"

class ExploreState : public GameState {
private:
    Player player;
    Map map;
    sf::Clock moveClock;
    const float moveCooldown = 0.15f;

public:
    ExploreState();
    void handleInput(Game& game, sf::RenderWindow& window) override;
    void update(Game& game) override;
    void render(Game& game, sf::RenderWindow& window) override;
};

