/*#include "Player.hpp"
#include "Map.hpp"

Player::Player(int x, int y){
    tilePos = {x,y};
    shape.setSize(sf::Vector2f((float)tileSize -4.f, (float)tileSize -4.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({(float) tilePos.x * tileSize + 2.f, (float) tilePos.y * tileSize + 2.f});
}


void Player::move(int x, int y, const std::vector<std::vector<int>> & map) {
    sf::Vector2i newPos = tilePos + sf::Vector2i(x,y);
    if(newPos.y >= 0 && newPos.y < (int) map.size() 
    && newPos.x >= 0 && newPos.x < (int) map[0].size()
    && map[newPos.y][newPos.x] == 0) {
        tilePos = newPos;
        shape.setPosition({(float) tilePos.x * tileSize + 2.f, (float) tilePos.y * tileSize + 2.f});
    }
}
 

void Player::move(int x, int y, const Map& map) {
    sf::Vector2i newPos = tilePos + sf::Vector2i(x, y);
    if (map.isWalkable(newPos.x, newPos.y)) {
        tilePos = newPos;
        shape.setPosition({
            (float)tilePos.x * tileSize + 2.f,
            (float)tilePos.y * tileSize + 2.f
        });
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
*/

#include "Player.hpp"
#include <iostream>

Player::Player(int x, int y, int ts) : tilePos(x, y), tileSize(ts) {
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize) - 4.f, static_cast<float>(tileSize) - 4.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition({
        static_cast<float>(tilePos.x * tileSize) + 2.f,
        static_cast<float>(tilePos.y * tileSize) + 2.f
    });
}

void Player::setTileSize(int ts) {
    tileSize = ts;
    shape.setSize(sf::Vector2f(static_cast<float>(tileSize) - 4.f, static_cast<float>(tileSize) - 4.f));
    shape.setPosition({
        static_cast<float>(tilePos.x * tileSize) + 2.f,
        static_cast<float>(tilePos.y * tileSize) + 2.f
    });
}

void Player::move(int dx, int dy, const Map& map) {
    sf::Vector2i newPos = tilePos + sf::Vector2i(dx, dy);
    if (map.isWalkable(newPos.x, newPos.y)) {
        tilePos = newPos;
        shape.setPosition({
            static_cast<float>(tilePos.x * tileSize) + 2.f,
            static_cast<float>(tilePos.y * tileSize) + 2.f
        });
    } else {
        // Debug: uncomment if needed
        // std::cout << "Blocked at " << newPos.x << "," << newPos.y << "\n";
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
