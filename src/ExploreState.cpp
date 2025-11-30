#include "ExploreState.hpp"
#include "Game.hpp"
#include <iostream>

ExploreState::ExploreState(Map& loadedMap, Player& playerRef)
    : map(loadedMap), player(playerRef)
{
    player = Player(1, 1, map.getTileSize());
}

void ExploreState::handleInput(Game&, sf::RenderWindow&) {
    if (battleStarted) {
        return;
    }

    sf::Vector2i oldPos = player.getTilePos();//

    if (moveClock.getElapsedTime().asSeconds() < moveCooldown) {
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        player.move(0, -1, map);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        player.move(0, 1, map);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        player.move(-1, 0, map);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        player.move(1, 0, map);
    } else {
        return;
    }
    moveClock.restart();

    if (player.getTilePos() != oldPos) {
        lastPlayerTile = oldPos;
    }
}

void ExploreState::update(Game& game) {
    if (battleStarted) return; // 
    sf::Vector2i pos = player.getTilePos();
    auto* tile = map.getTile(pos.x, pos.y);
    if (auto* exit = dynamic_cast<ExitTile*>(tile)) {
        game.switchRoom(exit->destination, exit->spawn);
        return;
    }

   for (auto& enemyPtr : map.getEnemies()) {
        if (!enemyPtr) continue;
        if (enemyPtr->getTilePos() == pos) {
            std::cout << "Battle initiated!\n";
            game.setPreviousPlayerPos(lastPlayerTile);
            game.startCombat(player, enemyPtr);
            return;
        }
    }
}

void ExploreState::render(Game&, sf::RenderWindow& window) {
    window.draw(map);
    window.draw(player);
}

void ExploreState::setPlayerPos(sf::Vector2i pos) {
    player = Player(pos.x, pos.y, map.getTileSize());
}

void ExploreState::resetBattleFlag() {
    battleStarted = false;
}