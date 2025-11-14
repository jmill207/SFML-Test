/*#include "Map.hpp"

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
*/

#include "Map.hpp"
#include "Tile.hpp"
#include "WallTile.hpp"
#include "GrassTile.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

bool Map::loadFromJSON(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filename << "\n";
        return false;
    }

    nlohmann::json j;
    file >> j;

    tileSize = j.value("tileSize", 32);
    tiles.clear();

    if (!j.contains("tiles") || !j["tiles"].is_array()) {
        std::cerr << "Map JSON has no 'tiles' array\n";
        return false;
    }

    for (auto& row : j["tiles"]) {
        if (!row.is_array()) continue;
        std::vector<std::unique_ptr<Tile>> tileRow;
        for (auto& type : row) {
            std::string t = type.get<std::string>();
            if (t == "Wall") {
                tileRow.push_back(std::make_unique<WallTile>(tileSize));
            } else if (t == "Grass") {
                tileRow.push_back(std::make_unique<GrassTile>(tileSize));
            } else {
                // fallback -> treat unknown as Grass for safety
                tileRow.push_back(std::make_unique<GrassTile>(tileSize));
            }
        }
        tiles.push_back(std::move(tileRow));
    }

    // set positions
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            tiles[y][x]->setPosition(x, y);
        }
    }

    return true;
}

bool Map::isWalkable(int x, int y) const {
    if (y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) return false;
    return tiles[y][x]->isWalkable();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            tiles[y][x]->draw(target, states);
        }
    }
}
