#pragma once
#include "Character.hpp"
#include "Vec2i.hpp"

class Entity {
private:
    Vec2i tilePos;
    Character stats;
public:
    Entity(int x, int y) : tilePos(x,y), stats("Enemy",20,4,3,1,2,3) {}
    Vec2i getTilePos() const { return tilePos; }
    Character& getStats() { return stats; }
    char toChar() const { return 'E'; }
};