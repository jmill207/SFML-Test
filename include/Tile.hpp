/*#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Tile : public sf::Drawable {
    protected:
        sf::RectangleShape shape;
        int size;
    public:
        Tile(int size = 32) : size(size) {
            shape.setSize({(float)size, (float)size});
        }

        virtual bool isWalkable() const { return true; }
        virtual std::string getType() const { return "Tile"; }

        void setPosition(int x, int y) {
            shape.setPosition(sf::Vector2f((float)x * size, (float)y * size));
        }

        void setColor(const sf::Color& color) {
            shape.setFillColor(color);
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(shape, states);
        }
};*/

#pragma once
#include <SFML/Graphics.hpp>

class Tile {
protected:
    sf::RectangleShape shape;
    bool walkable = true;
    int tileSize = 32;
public:
    Tile(int size = 32);
    virtual ~Tile() = default;

    virtual void setPosition(int x, int y);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual bool isWalkable() const { return walkable; }
};
