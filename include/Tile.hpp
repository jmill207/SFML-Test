#pragma once
#include <SFML/Graphics.hpp>

class Tile {
protected:
    sf::RectangleShape shape;
    bool walkable = true;
    int tileSize = 32;
public:
    Tile(int size = 32);
    virtual ~Tile() = default;

    virtual void setPosition(int x, int y);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual bool isWalkable() const { return walkable; }
};
