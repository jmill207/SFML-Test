/*#pragma once
#include "Tile.hpp"

class GrassTile : public Tile {
    public:
        GrassTile(int size = 32) : Tile(size) {
            shape.setFillColor(sf::Color(0,150,000));
        }
        bool isWalkable() const override { return false; }
        std::string getType() const override { return "Grass"; }
};

*/

#pragma once
#include "Tile.hpp"

class GrassTile : public Tile {
public:
    GrassTile(int size = 32);
};
