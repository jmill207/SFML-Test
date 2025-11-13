#pragma once
#include <SFML/Graphics.hpp>

class Game; // Forward declaration

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleInput(Game& game, sf::RenderWindow& window) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(Game& game, sf::RenderWindow& window) = 0;
};

