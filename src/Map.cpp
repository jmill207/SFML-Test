#include "Map.hpp"

Map::Map() {
    grid = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    tileShape.setSize({(float)tileSize, (float)tileSize});
}

bool Map::isWalkable(int x, int y) const {
    return (y >= 0 && y < (int)grid.size() &&
            x >= 0 && x < (int)grid[y].size() &&
            grid[y][x] == 0);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tileShape({tileSize, tileSize});
    for (int y = 0; y < (int)grid.size(); y++) {
        for (int x = 0; x < (int)grid[y].size(); x++) {
            tileShape.setPosition({(float)x * tileSize, (float)y * tileSize});
            tileShape.setFillColor(grid[y][x] == 1 ? sf::Color(100, 100, 100) : sf::Color(0, 150, 0));
            target.draw(tileShape, states);
        }
    }
}
