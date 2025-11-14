/*#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Player : public sf::Drawable {
    private:
        int tileSize = 32;
        sf::Vector2i tilePos;
        sf::RectangleShape shape;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
    public:
        Player(int startX, int startY);
        sf::Vector2i getTilePosition() const {
            return tilePos;
        }
        void move(int x, int y, const Map& map);
        int hp;
        int atk;
};
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Player : public sf::Drawable {
private:
    sf::Vector2i tilePos;
    sf::RectangleShape shape;
    int tileSize = 32;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Player(int x = 0, int y = 0, int tileSize = 32);
    void move(int dx, int dy, const Map& map);
    sf::Vector2i getTilePos() const { return tilePos; }
    void setTileSize(int ts);
};

