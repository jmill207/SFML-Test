#include "Game.hpp"
#include "ExploreState.hpp"
#include "BattleState.hpp"
#include "Entity.hpp"
#include <iostream>
#include <cstdlib>

Game::Game() : window(sf::VideoMode({1000, 600}), "RPG") , player(1,1,32) {
    maps.resize(4);
    if (!maps[0].loadFromJSON("data/maps/room0.json") || 
        !maps[1].loadFromJSON("data/maps/room1.json") || 
        !maps[2].loadFromJSON("data/maps/room2.json") ||
        !maps[3].loadFromJSON("data/maps/room3.json")) {
        std::cerr << "Failed to load map JSON\n";
        std::exit(EXIT_FAILURE);
    }

    maps[0].addEnemy(std::make_shared<Entity>(1, 3, maps[0].getTileSize()));//
    maps[1].addEnemy(std::make_shared<Entity>(4, 5, maps[1].getTileSize()));//
    maps[2].addEnemy(std::make_shared<Entity>(2, 2, maps[2].getTileSize()));//
    maps[3].addEnemy(std::make_shared<Entity>(6, 1, maps[3].getTileSize()));//

    changeState(std::make_unique<ExploreState>(maps[currRoom], player));
}

void Game::run() {
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
            currentState->handleInput(*this, window);
        }

        if (nextState) {
            currentState = std::move(nextState);
        }

        currentState->update(*this);
        window.clear();
        currentState->render(*this, window);
        window.display();
    }
}


void Game::changeState(std::unique_ptr<GameState> newState) {
    nextState = std::move(newState);
}

void Game::switchRoom(int idx, sf::Vector2i spawn) {
    this->currRoom = idx;
    auto state = std::make_unique<ExploreState>(maps[currRoom], player);
    state->setPlayerPos(spawn);
    changeState(std::move(state));
}

void Game::startCombat(Player& playerRef, std::shared_ptr<Entity> enemyPtr) {
    changeState(std::make_unique<BattleState>(playerRef, enemyPtr, *this));
}

void Game::endCombat(bool ranAway, sf::Vector2i previousPos) {
    auto temp = std::make_unique<ExploreState>(maps[currRoom], player);
    temp->resetBattleFlag();
    if (ranAway && previousPos.x != -1) {
        temp->setPlayerPos(previousPos);
    }
    changeState(std::move(temp));
}