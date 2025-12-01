#include "Map.hpp"
#include "Tile.hpp"
#include "MapLoader.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

bool Map::loadFromJSON(const std::string& filename) {
    MapLoader jsonLoader;
    if (!jsonLoader.loadMap(filename, tiles)) {
        std::cerr << "Failed to load map via MapLoader: " << filename << "\n";
        return false;
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

void Map::removeEnemy(const std::shared_ptr<Entity>& e) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), e),enemies.end());
}

void Map::printMap(const Player& player) const {
    for (int y = 0; y < getHeight(); ++y) {
        for (int x = 0; x < getWidth(); ++x) {
            if (player.getTilePos().x == x && player.getTilePos().y == y) {
                std::cout << 'P';
                continue;
            }
            bool enemyHere = false;
            for (const auto& e : enemies) {
                if (e && e->getTilePos().x == x && e->getTilePos().y == y) {
                    std::cout << 'E';
                    enemyHere = true;
                    break;
                }
            }
            if (enemyHere) continue;

            Tile* t = tiles[y][x].get();
            if (dynamic_cast<WallTile*>(t)) {
                std::cout << '#';
            } else if (dynamic_cast<ExitTile*>(t)) {
                std::cout << 'X';
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
}