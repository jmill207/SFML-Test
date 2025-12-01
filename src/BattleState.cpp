#include "BattleState.hpp"
#include "Game.hpp"
#include "ExploreState.hpp"
#include <iostream>
#include <limits>

BattleState::BattleState(Player& p, std::shared_ptr<Entity> e, Game& g)
    : player(p), enemy(std::move(e)), game(g)
{
    std::cout << "Battle started against " << enemy->getStats().getName() << "!\n";
    printStatus();
}

void BattleState::handleInput(Game& game) {
    if (battleOver) return;

    if (playerTurn) {
        std::cout << "\nChoose action:\n";
        for (size_t i = 0; i < menuOptions.size(); ++i) {
            std::cout << (i + 1) << ". " << menuOptions[i] << "\n";
        }
        std::cout << "> ";

        int choice = 0;
        std::cin >> choice;

        while(std::cin.fail() || choice < 1 || choice > static_cast<int>(menuOptions.size())) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again: ";
            std::cin >> choice;
        }

        std::string action = menuOptions[choice - 1];

        if (action == "Attack") {
            playerAttack();
            playerTurn = false;
        } 
        else if (action == "Run") {
            std::cout << "You ran away!\n";
            battleOver = true;
            game.endCombat(true, game.getPreviousPlayerPos());
            return;
        } 
        else if (action == "Items") {
            std::cout << "Items not implemented yet!\n";
        }

        if (enemy->getStats().isDead()) {
            std::cout << enemy->getStats().getName() << " defeated!\n";
            game.getMaps()[game.getCurrRoom()].removeEnemy(enemy);
            battleOver = true;
            game.endCombat();
            return;
        }

    } else {
        enemyAttack();
        playerTurn = true;

        if (player.getStats().isDead()) {
            std::cout << "Player defeated!\n";
            battleOver = true;
            game.endCombat();
            return;
        }
    }

    printStatus();
}

void BattleState::update(Game&) {
    // All logic handled in handleInput
}

void BattleState::render(Game&) {
    // All rendering now via console in handleInput/printStatus
}

void BattleState::playerAttack() {
    int damage = std::max(0, player.getStats().getAttack() - enemy->getStats().getDefense());
    enemy->getStats().takeDamage(damage);
    std::cout << "You hit " << enemy->getStats().getName() << " for " << damage << " damage!\n";
}

void BattleState::enemyAttack() {
    int damage = std::max(0, enemy->getStats().getAttack() - player.getStats().getDefense());
    player.getStats().takeDamage(damage);
    std::cout << enemy->getStats().getName() << " hits you for " << damage << " damage!\n";
}

void BattleState::printStatus() {
    std::cout << "\nPlayer HP: " << player.getStats().getHP() << "/" << player.getStats().getMaxHP() << "\n";
    std::cout << enemy->getStats().getName() << " HP: " << enemy->getStats().getHP() << "/" << enemy->getStats().getMaxHP() << "\n";
}