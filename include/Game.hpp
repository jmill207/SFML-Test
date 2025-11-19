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
    std::vector<Map> maps;
    int currRoom = 0;
public:
    Game();
    void run();
    void changeState(std::unique_ptr<GameState> newState);

    sf::RenderWindow& getWindow() { return window; }
    std::vector<Map>& getMaps() { return maps; }
    int getCurrRoom() const { return currRoom ;}
    void switchRoom(int idx, sf::Vector2i spawn);
};

