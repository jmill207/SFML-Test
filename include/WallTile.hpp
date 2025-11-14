/*#pragma once
#include "Tile.hpp"

class WallTile : public Tile {
    public:
        WallTile(int size = 32) : Tile(size) {
            shape.setFillColor(sf::Color(100,100,100));
        }
        bool isWalkable() const override { return false; }
        std::string getType() const override { return "Wall"; }
};*/

#pragma once
#include "Tile.hpp"

class WallTile : public Tile {
public:
    WallTile(int size = 32);
    bool isWalkable() const override { return false; }
};
