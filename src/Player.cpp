#include "Player.hpp"
#include <iostream>

Player::Player(int x, int y, int ts) 
    : tilePos{x, y}, stats("Hero", 30, 5, 5, 2, 3, 4)
{}

void Player::move(int dx, int dy, const Map& map) {
    Vec2i newPos{tilePos.x + dx, tilePos.y + dy};
    if (map.isWalkable(newPos.x, newPos.y)) {
        tilePos = newPos;
    }
}