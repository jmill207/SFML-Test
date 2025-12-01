#pragma once
#include "Character.hpp"
#include "Vec2i.hpp"
#include "Map.hpp"

class Map;

class Player {
private:
    Vec2i tilePos;
    Character stats;
public:
    Player(int x = 0, int y = 0, int tileSize = 32);
    void move(int dx, int dy, const Map& map);
    Vec2i getTilePos() const { return tilePos; }
    void setTilePos(const Vec2i& pos) { tilePos = pos; }
    Character& getStats() { return stats; }
};
