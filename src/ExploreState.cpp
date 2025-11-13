#include "ExploreState.hpp"
#include "Game.hpp"

ExploreState::ExploreState()
    : player(2, 2) {}

void ExploreState::handleInput(Game&, sf::RenderWindow&) {
    if (moveClock.getElapsedTime().asSeconds() < moveCooldown) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move(0, -1, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move(0, 1, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move(-1, 0, map);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move(1, 0, map);
    else return;

    moveClock.restart();
}

void ExploreState::update(Game&) {
    // Any state-specific updates later
}

void ExploreState::render(Game&, sf::RenderWindow& window) {
    window.draw(map);
    window.draw(player);
}

