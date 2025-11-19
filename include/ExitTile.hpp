#pragma once
#include "Tile.hpp"

class ExitTile : public Tile {
public:
    int destination;
    sf::Vector2i spawn;
    ExitTile(int size = 32, int destination = 0, sf::Vector2i spawn = {0,0})
        : Tile(size), destination(destination), spawn(spawn) 
    {
        shape.setFillColor(sf::Color(0, 0, 255));
        walkable = true;
    }
    bool isWalkable() const override { return true; }
};