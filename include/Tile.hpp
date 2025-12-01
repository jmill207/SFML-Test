#pragma once
#include "Vec2i.hpp"

class Tile {
protected:
    bool walkable = true;
public:
    Tile() = default;
    virtual ~Tile() = default;
    virtual bool isWalkable() const { return walkable; }
    virtual char getSymbol() const { return '.'; }
};

class WallTile : public Tile {
public:
    WallTile() { walkable = false; }
    char getSymbol() const override { return '#'; }
};

class GrassTile : public Tile {
public:
    GrassTile() { walkable = true; }
    char getSymbol() const override { return ' '; }
};

class ExitTile : public Tile {
public:
    int destination = 0;
    Vec2i spawn;
    ExitTile(int dest, Vec2i sp) : destination(dest), spawn(sp) {}
    char getSymbol() const override { return 'E'; }
};