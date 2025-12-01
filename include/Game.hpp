#pragma once
#include "GameState.hpp"
#include "Player.hpp"
#include "Vec2i.hpp"
#include <memory>
#include "Map.hpp"
#include <vector>

class GameState;

class Game {
private:
    std::unique_ptr<GameState> currentState;
    std::vector<Map> maps;
    int currRoom = 0;
    std::unique_ptr<GameState> nextState;
    Vec2i previousPlayerPos { -1, -1 };
public:
    Player player; 

    Game();
    void run();
    void changeState(std::unique_ptr<GameState> newState);

    std::vector<Map>& getMaps() { return maps; }
    int getCurrRoom() const { return currRoom; }
    void switchRoom(int idx, Vec2i spawn);
    void startCombat(Player& playerRef, std::shared_ptr<Entity> enemyPtr);
    void endCombat(bool ranAway = false, Vec2i previousPos = {-1,-1});
    Vec2i getPreviousPlayerPos() const { return previousPlayerPos; }
    void setPreviousPlayerPos(Vec2i pos) { previousPlayerPos = pos; }
};
