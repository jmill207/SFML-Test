#pragma once
#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Tile.hpp" 

class MapLoader {
public:
    bool loadMap(const std::string& filename, std::vector<std::vector<std::unique_ptr<Tile>>>& outTiles);
};
