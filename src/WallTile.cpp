#include "WallTile.hpp"

WallTile::WallTile(int size) : Tile(size) {
    tileSize = size;
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize)));
    shape.setFillColor(sf::Color(80, 80, 80));
    walkable = false;
}
