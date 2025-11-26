#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Player.hpp"
#include <memory>
#include "Map.hpp"

class GameState;

class Game {
private:
    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;
    std::vector<Map> maps;
    int currRoom = 0;
    std::unique_ptr<GameState> nextState;
    sf::Vector2i previousPlayerPos;
public:
    Player player; 

    Game();
    void run();
    void changeState(std::unique_ptr<GameState> newState);

    sf::RenderWindow& getWindow() { return window; }
    std::vector<Map>& getMaps() { return maps; }
    int getCurrRoom() const { return currRoom ;}
    void switchRoom(int idx, sf::Vector2i spawn);
    void startCombat(Player& playerRef, std::shared_ptr<Entity> enemyPtr);
    void endCombat(bool ranAway = false, sf::Vector2i previousPos = {-1,-1});
    sf::Vector2i getPreviousPlayerPos() const { return previousPlayerPos; }
    void setPreviousPlayerPos(sf::Vector2i pos) { previousPlayerPos = pos; }
};