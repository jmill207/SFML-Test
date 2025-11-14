/*#include "ExploreState.hpp"
#include "Game.hpp"

ExploreState::ExploreState()
    : player(2, 2) {}

void ExploreState::handleInput(Game&, sf::RenderWindow&) {
    if (moveClock.getElapsedTime().asSeconds() < moveCooldown) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move(0, -1, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move(0, 1, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move(-1, 0, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move(1, 0, map);
    else return;

    moveClock.restart();
}

void ExploreState::update(Game&) {
    // Any state-specific updates later
}

void ExploreState::render(Game&, sf::RenderWindow& window) {
    window.draw(map);
    window.draw(player);
}
*/

#include "ExploreState.hpp"
#include "Game.hpp"
#include <iostream>

ExploreState::ExploreState(Map& loadedMap)
    : map(loadedMap), player(0, 0, loadedMap.getTileSize())
{
    sf::Vector2i start = findWalkableStart();
    player = Player(start.x, start.y, map.getTileSize());
}

sf::Vector2i ExploreState::findWalkableStart() const {
    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            if (map.isWalkable(x, y)) {
                // place slightly inset from edge if you like; returning first
                std::cout << "Spawning player at: " << x << "," << y << "\n";
                return {x, y};
            }
        }
    }
    std::cerr << "No walkable tile found; defaulting to (0,0)\n";
    return {0, 0};
}

void ExploreState::handleInput(Game&, sf::RenderWindow&) {
    if (moveClock.getElapsedTime().asSeconds() < moveCooldown) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move(0, -1, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move(0, 1, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move(-1, 0, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move(1, 0, map);
    else return;

    moveClock.restart();
}

void ExploreState::update(Game&) {
    // placeholder
}

void ExploreState::render(Game&, sf::RenderWindow& window) {
    window.draw(map);
    window.draw(player);
}

