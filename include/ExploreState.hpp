#pragma once
#include "GameState.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>

class ExploreState : public GameState {
private:
    Map& map;
    Player player;
    sf::Clock moveClock;
    float moveCooldown = 0.12f;

    sf::Vector2i findWalkableStart() const;

public:
    ExploreState(Map& loadedMap);

    void handleInput(Game&, sf::RenderWindow&) override;
    void update(Game&) override;
    void render(Game&, sf::RenderWindow&) override;
};


