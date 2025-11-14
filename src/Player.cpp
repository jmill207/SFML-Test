#include "Player.hpp"
#include <iostream>

Player::Player(int x, int y, int ts) : tilePos(x, y), tileSize(ts) {
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize) - 4.f, static_cast<float>(tileSize) - 4.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({
        static_cast<float>(tilePos.x * tileSize) + 2.f,
        static_cast<float>(tilePos.y * tileSize) + 2.f
    });
}

void Player::setTileSize(int ts) {
    tileSize = ts;
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize) - 4.f, static_cast<float>(tileSize) - 4.f));
    shape.setPosition({
        static_cast<float>(tilePos.x * tileSize) + 2.f,
        static_cast<float>(tilePos.y * tileSize) + 2.f
    });
}

void Player::move(int dx, int dy, const Map& map) {
    sf::Vector2i newPos = tilePos + sf::Vector2i(dx, dy);
    if (map.isWalkable(newPos.x, newPos.y)) {
        tilePos = newPos;
        shape.setPosition({
            static_cast<float>(tilePos.x * tileSize) + 2.f,
            static_cast<float>(tilePos.y * tileSize) + 2.f
        });
    } else {
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
