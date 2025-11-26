#include "Map.hpp"
#include "Tile.hpp"
#include "MapLoader.hpp"
#include "WallTile.hpp"
#include "GrassTile.hpp"
#include "ExitTile.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

bool Map::loadFromJSON(const std::string& filename) {
    MapLoader jsonLoader;
    if (!jsonLoader.loadMap(filename, tileSize, tiles)) {
        std::cerr << "Failed to load map via MapLoader: " << filename << "\n";
        return false;
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

    for (const auto& e : enemies) {
        if (e) {
            target.draw(*e, states); 
        }
    }
}