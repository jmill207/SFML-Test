#pragma once
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class MapLoader {
public:
    MapLoader() = default;

    std::vector<std::vector<int>> loadMap(const std::string& filename, int& outTileSize) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open map file: " + filename);
        }

        nlohmann::json j;
        file >> j;

        std::vector<std::vector<int>> mapData;

        for (auto& row : j["tiles"]) {
            std::vector<int> tileRow;
            for (auto& tile : row) {
                tileRow.push_back(tile.get<int>());
            }
            mapData.push_back(tileRow);
        }

        outTileSize = j.value("tileSize", 32);

        return mapData;
    }
};
