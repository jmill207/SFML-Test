#include "Game.hpp"
#include "ExploreState.hpp"
#include "BattleState.hpp"
#include "Entity.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>

Game::Game() : player(1,1,32) {
    maps.resize(4);
    if (!maps[0].loadFromJSON("data/maps/room0.json") || 
        !maps[1].loadFromJSON("data/maps/room1.json") || 
        !maps[2].loadFromJSON("data/maps/room2.json") ||
        !maps[3].loadFromJSON("data/maps/room3.json")) {
        std::cerr << "Failed to load map JSON\n";
        std::exit(EXIT_FAILURE);
    }

    maps[0].addEnemy(std::make_shared<Entity>(1, 3));
    maps[1].addEnemy(std::make_shared<Entity>(4, 5));
    maps[2].addEnemy(std::make_shared<Entity>(2, 2));
    maps[3].addEnemy(std::make_shared<Entity>(6, 1));

    changeState(std::make_unique<ExploreState>(maps[currRoom], player));
}

void Game::run() {
    while (true) {
        if (nextState) {
            currentState = std::move(nextState);
        }
        currentState->handleInput(*this);

        currentState->update(*this);
        currentState->render(*this);
        std::cout << "Press Q to quit, or Enter to continue...\n";
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty() && (input[0] == 'q' || input[0] == 'Q')) {
            break;
        }
    }
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    nextState = std::move(newState);
}

void Game::switchRoom(int idx, Vec2i spawn) {
    this->currRoom = idx;
    auto state = std::make_unique<ExploreState>(maps[currRoom], player);
    state->setPlayerPos(spawn);
    changeState(std::move(state));
}

void Game::startCombat(Player& playerRef, std::shared_ptr<Entity> enemyPtr) {
    changeState(std::make_unique<BattleState>(playerRef, enemyPtr, *this));
}

void Game::endCombat(bool ranAway, Vec2i previousPos) {
    auto temp = std::make_unique<ExploreState>(maps[currRoom], player);
    temp->resetBattleFlag();
    if (ranAway && previousPos.x != -1) {
        temp->setPlayerPos(previousPos);
    }
    changeState(std::move(temp));
}