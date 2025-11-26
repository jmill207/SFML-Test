#include "MapLoader.hpp"

bool MapLoader::loadMap(const std::string& filename, int& outTileSize, std::vector<std::vector<std::unique_ptr<Tile>>>& outTiles) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filename << "\n";
        return false;
    }

    nlohmann::json j;
    file >> j;

    outTileSize = j.value("tileSize", 32);
    outTiles.clear();

    if (!j.contains("tiles") || !j["tiles"].is_array()) {
        std::cerr << "Map JSON has no 'tiles' array\n";
        return false;
    }

    int y = 0;
    for (auto& row : j["tiles"]) {
        if (!row.is_array()) {
            continue;
        }
        std::vector<std::unique_ptr<Tile>> tileRow;
        int x = 0;
        for (auto& cell : row) {
            std::string t = "Grass";
            if (cell.is_string()) {
                t = cell.get<std::string>();
            } else if (cell.is_object()) {
                t = cell.value("type", "Grass");
            }
            if (t == "Wall") tileRow.push_back(std::make_unique<WallTile>(outTileSize));
            else if (t == "Exit") {
                int destination = cell.value("destination", 0);
                std::vector<int> spawnArea = cell.value("spawn", std::vector<int>{0,0});
                sf::Vector2i spawn(spawnArea[0], spawnArea[1]);
                tileRow.push_back(std::make_unique<ExitTile>(outTileSize, destination, spawn));
            } else {
                tileRow.push_back(std::make_unique<GrassTile>(outTileSize));
            }
            ++x;
        }
        outTiles.push_back(std::move(tileRow));
        ++y;
    }

    return true;
}