#include "Player.hpp"
#include "Map.hpp"

Player::Player(int x, int y){
    tilePos = {x,y};
    shape.setSize(sf::Vector2f((float)tileSize -4.f, (float)tileSize -4.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({(float) tilePos.x * tileSize + 2.f, (float) tilePos.y * tileSize + 2.f});
}

void Player::move(int x, int y, const Map& map) {
    sf::Vector2i newPos = tilePos + sf::Vector2i(x, y);
    if (map.isWalkable(newPos.x, newPos.y)) {
        tilePos = newPos;
        shape.setPosition({
            (float)tilePos.x * tileSize + 2.f,
            (float)tilePos.y * tileSize + 2.f
        });
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
