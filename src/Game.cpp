#include "Game.hpp"
#include "ExploreState.hpp"
#include <iostream>
#include <cstdlib>

Game::Game() : window(sf::VideoMode({1000, 600}), "RPG") {
    maps.resize(3);
    if (!maps[0].loadFromJSON("data/maps/room0.json") || 
        !maps[1].loadFromJSON("data/maps/room1.json") || 
        !maps[2].loadFromJSON("data/maps/room2.json") ) {
        std::cerr << "Failed to load map JSON\n";
        std::exit(EXIT_FAILURE);
    }
    changeState(std::make_unique<ExploreState>(maps[currRoom]));
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
        currentState->update(*this);
        window.clear();
        currentState->render(*this, window);
        window.display();
    }
}


void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}

void Game::switchRoom(int idx, sf::Vector2i spawn) {
    this->currRoom = idx;
    auto state = std::make_unique<ExploreState>(maps[currRoom]);
    state->setPlayerPos(spawn);
    changeState(std::move(state));
}