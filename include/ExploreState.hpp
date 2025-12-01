#pragma once
#include "GameState.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Entity.hpp"
#include "Vec2i.hpp"

class ExploreState : public GameState {
private:
    Map& map;
    Player& player; 
    bool battleStarted = false;
    Vec2i lastPlayerTile{0,0};
public:
    ExploreState(Map& loadedMap, Player& playerRef);
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;
    void setPlayerPos(Vec2i pos);
    void resetBattleFlag();
};
