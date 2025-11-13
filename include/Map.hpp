#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map : public sf::Drawable {
private:
    std::vector<std::vector<int>> grid;
    sf::RectangleShape tileShape;
    float tileSize = 32;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Map();
    bool isWalkable(int x, int y) const;
    int getTileSize() const { return tileSize; }
};
