#include "ExploreState.hpp"
#include "Game.hpp"
#include <iostream>

ExploreState::ExploreState(Map& loadedMap, Player& playerRef)
    : map(loadedMap), player(playerRef)
{
    player.setTilePos({1, 1});
}

void ExploreState::handleInput(Game& game) {
    if (battleStarted) return;

    Vec2i oldPos = player.getTilePos();
    char input;
    std::cout << "Move (W/A/S/D): ";
    std::cin >> input;

    if (input == 'w' || input == 'W') {
        player.move(0, -1, map);
    } else if (input == 's' || input == 'S') {
        player.move(0, 1, map);
    } else if (input == 'a' || input == 'A') {
        player.move(-1, 0, map);
    } else if (input == 'd' || input == 'D') {
        player.move(1, 0, map);
    } else {
        return;
    }

    if (!(player.getTilePos() == oldPos)) {
        lastPlayerTile = oldPos;
    }
}

void ExploreState::update(Game& game) {
    if (battleStarted) return;

    auto pos = player.getTilePos();
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

void ExploreState::render(Game&) {
    map.printMap(player);
}

void ExploreState::setPlayerPos(Vec2i pos) {
    player.setTilePos(pos);
}

void ExploreState::resetBattleFlag() {
    battleStarted = false;
}