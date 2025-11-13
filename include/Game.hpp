#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameState.hpp"

class Game {
private:
    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;

public:
    Game();
    void run();

    void changeState(std::unique_ptr<GameState> newState);
    sf::RenderWindow& getWindow() { return window; }
};