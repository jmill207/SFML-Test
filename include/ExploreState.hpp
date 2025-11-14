/*#pragma once
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
};*/

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
    float moveCooldown = 0.12f; // seconds

    sf::Vector2i findWalkableStart() const;

public:
    ExploreState(Map& loadedMap);

    void handleInput(Game&, sf::RenderWindow&) override;
    void update(Game&) override;
    void render(Game&, sf::RenderWindow&) override;
};


