#include "ExploreState.hpp"
#include "Game.hpp"
#include <iostream>

ExploreState::ExploreState(Map& loadedMap)
    : map(loadedMap), player(0, 0, loadedMap.getTileSize())
{
    player = Player(1, 1, map.getTileSize());
}

sf::Vector2i ExploreState::findWalkableStart() const {
    for (int y = 0; y < map.getHeight(); ++y) {
        for (int x = 0; x < map.getWidth(); ++x) {
            if (map.isWalkable(x, y)) {
                std::cout << "Spawning player at: " << x << "," << y << "\n";
                return {x, y};
            }
        }
    }
    std::cerr << "No walkable tile found; defaulting to (0,0)\n";
    return {0, 0};
}

void ExploreState::handleInput(Game&, sf::RenderWindow&) {
    if (moveClock.getElapsedTime().asSeconds() < moveCooldown) {
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        player.move(0, -1, map);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        player.move(0, 1, map);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player.move(-1, 0, map);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player.move(1, 0, map);
    } else {
        return;
    }
    moveClock.restart();
}

void ExploreState::update(Game& game) {
    sf::Vector2i pos = player.getTilePos();
    auto* tile = map.getTile(pos.x, pos.y);
    if (auto* exit = dynamic_cast<ExitTile*>(tile)) {
        game.switchRoom(exit->destination, exit->spawn);
    }
}

void ExploreState::render(Game&, sf::RenderWindow& window) {
    window.draw(map);
    window.draw(player);
}

void ExploreState::setPlayerPos(sf::Vector2i pos) {
    player = Player(pos.x, pos.y, map.getTileSize());
}