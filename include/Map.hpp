#pragma once
#include <vector>
#include <memory>
#include "Tile.hpp"
#include "Player.hpp"
#include "Entity.hpp"

class Player;

class Map {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::shared_ptr<Entity>> enemies;
public:
    bool loadFromJSON(const std::string& filename);
    Map() = default;
    bool isWalkable(int x, int y) const;
    Tile* getTile(int x,int y) const;
    int getWidth() const { return tiles.empty() ? 0 : (int)tiles[0].size(); }
    int getHeight() const { return (int)tiles.size(); }
    void addEnemy(std::shared_ptr<Entity> e) { enemies.push_back(e); }
    std::vector<std::shared_ptr<Entity>>& getEnemies() { return enemies; }
    void removeEnemy(const std::shared_ptr<Entity>& e);
    void printMap(const Player& player) const;
    void setTiles(std::vector<std::vector<std::unique_ptr<Tile>>>&& t) { tiles = std::move(t); }
};