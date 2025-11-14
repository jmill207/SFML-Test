#include "Tile.hpp"

Tile::Tile(int size) : tileSize(size) {
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
    shape.setFillColor(sf::Color(150, 150, 150));
    walkable = true;
}

void Tile::setPosition(int x, int y) {
    shape.setPosition(sf::Vector2f((float)x * tileSize, (float)y * tileSize));
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
