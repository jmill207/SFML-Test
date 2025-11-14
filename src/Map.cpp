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
                tileRow.push_back(std::make_unique<GrassTile>(tileSize));
            }
        }
        tiles.push_back(std::move(tileRow));
    }

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
