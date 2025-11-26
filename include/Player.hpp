#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "Map.hpp"

class Player : public sf::Drawable {
private:
    sf::Vector2i tilePos;
    sf::RectangleShape shape;
    int tileSize = 32;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Character stats;
public:
    Player(int x = 0, int y = 0, int tileSize = 32);
    void move(int dx, int dy, const Map& map);
    sf::Vector2i getTilePos() const { return tilePos; }
    void setTileSize(int ts);
    Character& getStats() { return stats; }
};