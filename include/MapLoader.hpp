#pragma once
#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Tile.hpp" 
#include "GrassTile.hpp"
#include "WallTile.hpp"
#include "ExitTile.hpp"

class MapLoader {
public:
    bool loadMap(const std::string& filename, int& outTileSize,
                 std::vector<std::vector<std::unique_ptr<Tile>>>& outTiles);
};
