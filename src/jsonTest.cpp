
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    std::ifstream file("data/maps/map1.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open map1.json\n";
        return 1;
    }

    json mapData;
    file >> mapData;

    std::cout << "Loaded map: " << mapData["name"] << "\n";
    std::cout << "Width: " << mapData["width"] << ", Height: " << mapData["height"] << "\n";
    return 0;
}
