#pragma once
struct Vec2i {
    int x;
    int y;
    Vec2i(int _x=0, int _y=0) : x(_x), y(_y) {}
    Vec2i operator+(const Vec2i& other) const { return Vec2i(x + other.x, y + other.y); }
    bool operator==(const Vec2i& other) const { return x == other.x && y == other.y; }
};