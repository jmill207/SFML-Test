#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "Tile.hpp"
#include "GrassTile.hpp"
#include "WallTile.hpp"

class Map : public sf::Drawable {
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    int tileSize = 32;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Map() = default;
    bool loadFromJSON(const std::string& filename);

    bool isWalkable(int x, int y) const;
    int getTileSize() const { return tileSize; }

    int getWidth() const { return tiles.empty() ? 0 : static_cast<int>(tiles[0].size()); }
    int getHeight() const { return static_cast<int>(tiles.size()); }
};
