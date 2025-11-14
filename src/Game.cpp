/*#include "Game.hpp"
#include "ExploreState.hpp"

Game::Game() : window(sf::VideoMode({1000, 600}), "RPG") {
    changeState(std::make_unique<ExploreState>());
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
            currentState->update(*this);

            window.clear();
            currentState->render(*this, window);
            window.display();
        }
    }
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}
*/

#include "Game.hpp"
#include "ExploreState.hpp"
#include <iostream>
#include <cstdlib>

Game::Game() : window(sf::VideoMode({1000, 600}), "RPG") {
    // load into the Game-owned map member
    if (!map.loadFromJSON("data/maps/map2.json")) {
        std::cerr << "Failed to load map JSON\n";
        std::exit(EXIT_FAILURE);
    }

    // Create the initial ExploreState that references Game::map
    changeState(std::make_unique<ExploreState>(map));
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
            currentState->update(*this);

            window.clear();
            currentState->render(*this, window);
            window.display();
        }
    }
}

void Game::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}
