#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include <memory>
#include "Map.hpp"

class GameState;

class Game {
private:
    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;
    Map map;
public:
    Game();
    void run();
    void changeState(std::unique_ptr<GameState> newState);

    sf::RenderWindow& getWindow() { return window; }
    Map& getMap() { return map; }
};

