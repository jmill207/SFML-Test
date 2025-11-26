#pragma once
#include "GameState.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class ExploreState : public GameState {
private:
    Map& map;
    Player& player; 
    sf::Clock moveClock;
    float moveCooldown = 0.12f;
    bool battleStarted = false;
    sf::Vector2i lastPlayerTile;
public:
    ExploreState(Map& loadedMap, Player& playerRef);
    void handleInput(Game&, sf::RenderWindow&) override;
    void update(Game& game) override;
    void render(Game&, sf::RenderWindow&) override;
    void setPlayerPos(sf::Vector2i pos);
    void resetBattleFlag();
};