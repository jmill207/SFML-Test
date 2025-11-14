#include "GrassTile.hpp"

GrassTile::GrassTile(int size) : Tile(size) {
    tileSize = size;
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
    shape.setFillColor(sf::Color(100, 200, 100));
    walkable = true;
}
