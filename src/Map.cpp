#include "Map.hpp"
#include "Tile.hpp"
#include "WallTile.hpp"
#include "GrassTile.hpp"
#include "ExitTile.hpp"
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
        for (auto& cell : row) {
            if(cell.is_string()) {
                std::string t = cell.get<std::string>();
                if (t == "Wall") {
                    tileRow.push_back(std::make_unique<WallTile>(tileSize));
                } else if (t == "Grass") {
                    tileRow.push_back(std::make_unique<GrassTile>(tileSize));
                } else {
                    tileRow.push_back(std::make_unique<GrassTile>(tileSize));
                }
            } else if (cell.is_object()) {
                std::string t =  cell.value("type", "Grass");
                if (t == "Exit") {
                    int destination =  cell.value("destination", 0);
                    std::vector<int> spawnArea = cell.value("spawn", std::vector<int>{0,0});
                    sf::Vector2i spawn(spawnArea[0], spawnArea[1]);
                    tileRow.push_back(std::make_unique<ExitTile>(tileSize, destination, spawn));
                } else if (t == "Wall") {
                    tileRow.push_back(std::make_unique<WallTile>(tileSize));
                } else {
                    tileRow.push_back(std::make_unique<GrassTile>(tileSize));
                }
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
    if (y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) {
        return false;
    }
    return tiles[y][x]->isWalkable();
}

Tile* Map::getTile(int x, int y) const {
    if(y < 0 || y >= getHeight() || x < 0 || x >= getWidth()) {
        return nullptr;
    }
    return tiles[y][x].get();
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            tiles[y][x]->draw(target, states);
        }
    }
}
