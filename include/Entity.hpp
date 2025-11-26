#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"

class Entity : public sf::Drawable {
private:
    sf::Vector2i tilePos;
    sf::RectangleShape shape;
    Character stats;

public:
    Entity(int x, int y, int tileSize)
        : tilePos(x, y),
          stats("Enemy", 20, 4, 3, 1, 2, 3)
    {
        shape.setSize(sf::Vector2f(tileSize - 4, tileSize - 4));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(sf::Vector2f((float)x * tileSize, (float)y * tileSize));
    }

    sf::Vector2i getTilePos() const { return tilePos; }
    Character& getStats() { return stats; }

    virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const override {
        t.draw(shape, s);
    }
};
