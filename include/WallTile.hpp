#pragma once
#include "Tile.hpp"

class WallTile : public Tile {
public:
    WallTile(int size = 32);
    bool isWalkable() const override { return false; }
};
