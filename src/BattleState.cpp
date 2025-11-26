#include "BattleState.hpp"
#include "Game.hpp"
#include "ExploreState.hpp"

BattleState::BattleState(Player& p, std::shared_ptr<Entity> e, Game& gameRef)
    : player(p), enemy(std::move(e)), game(gameRef), playerText(font), enemyText(font), infoText(font)
{
    setupText();
    enemyPlaceholder.setSize(sf::Vector2f(80, 80));
    enemyPlaceholder.setFillColor(sf::Color::Red);
    enemyPlaceholder.setPosition(sf::Vector2f(400.f, 200.f));
}

void BattleState::setupText() {
    if (!font.openFromFile("data/fonts/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    bg.setSize(sf::Vector2f(1000.f, 600.f));
    bg.setFillColor(sf::Color::Black);

    playerText.setFont(font);
    playerText.setCharacterSize(20);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(sf::Vector2f(50.f, 500.f));

    playerHPBar.setSize(sf::Vector2f(200.f, 20.f));
    playerHPBar.setFillColor(sf::Color::Green);
    playerHPBar.setPosition(sf::Vector2f(200.f, 500.f));

    enemyText.setFont(font);
    enemyText.setCharacterSize(20);
    enemyText.setFillColor(sf::Color::White);
    enemyText.setPosition(sf::Vector2f(50.f, 50.f));

    enemyHPBar.setSize(sf::Vector2f(200.f, 20.f));
    enemyHPBar.setFillColor(sf::Color::Red);
    enemyHPBar.setPosition(sf::Vector2f(250.f, 50.f));

    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Yellow);
    infoText.setPosition(sf::Vector2f(50.f, 550.f));
}

void BattleState::handleInput(Game& game, sf::RenderWindow& window) {
    if (battleOver) {
        return;
    }

    if (playerTurn) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            selectedOption = (selectedOption + menuOptions.size() - 1) % menuOptions.size();
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            selectedOption = (selectedOption + 1) % menuOptions.size();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            std::string choice = menuOptions[selectedOption];

            if (choice == "Attack") {
                playerAttack();
                playerTurn = false;
                updateText();
            }
            else if (choice == "Run") {
                infoText.setString("You ran away!");
                battleOver = true;
                game.endCombat(true, game.getPreviousPlayerPos());
            }
            else if (choice == "Items") {
                infoText.setString("Items not implemented yet!");
            }
        }

        if (player.getStats().getHP() <= 0) {
            infoText.setString("Player defeated!");
            battleOver = true;
            game.endCombat();
        }

        if (enemy->getStats().getHP() <= 0) {
            infoText.setString(enemy->getStats().getName() + " defeated!");
            game.getMaps()[game.getCurrRoom()].removeEnemy(enemy);
            battleOver = true;
            game.endCombat();
        }
    }
    else {
        enemyAttack();
        playerTurn = true;
        updateText();

        if (player.getStats().getHP() <= 0) {
            infoText.setString("Player defeated!");
            battleOver = true;
            game.endCombat();
        } else if (enemy->getStats().getHP() <= 0) {
            infoText.setString(enemy->getStats().getName() + " defeated!");
            game.getMaps()[game.getCurrRoom()].removeEnemy(enemy);
            battleOver = true;
            game.endCombat();
        }
    }
}

void BattleState::update(Game& game) {
    if (!playerTurn && !battleOver) {
        enemyAttack();
        playerTurn = true;
        updateText();

        if (player.getStats().getHP() <= 0) {
            std::cout << "Player defeated!\n";
            battleOver = true;
            game.endCombat(); 
        } else if (enemy->getStats().getHP() <= 0) {
            std::cout << "Enemy defeated!\n";
            game.getMaps()[game.getCurrRoom()].removeEnemy(enemy);
            battleOver = true;
            game.endCombat();
        }
    }
}

void BattleState::render(Game&, sf::RenderWindow& window) {
   window.draw(bg);
    enemyPlaceholder.setPosition(sf::Vector2f(400.f, 200.f));
    window.draw(enemyPlaceholder);

    window.draw(enemyText);
    window.draw(enemyHPBar);
    window.draw(playerText);
    window.draw(playerHPBar);

    window.draw(infoText);

    for (size_t i = 0; i < menuOptions.size(); ++i) {
        sf::Text optionText(font);
        optionText.setFont(font);
        optionText.setCharacterSize(20);
        optionText.setString(menuOptions[i]);
        optionText.setPosition(sf::Vector2f(600.f + i*120.f, 500.f));
        optionText.setFillColor(i == selectedOption ? sf::Color::Yellow : sf::Color::White);
        window.draw(optionText);
    }
}

void BattleState::updateText() {
    playerText.setString(player.getStats().getName());
    float playerHPPercent = float(player.getStats().getHP()) / player.getStats().getMaxHP();
    playerHPBar.setSize(sf::Vector2f(200.f * playerHPPercent, 20.f));

    enemyText.setString(enemy->getStats().getName());
    float enemyHPPercent = float(enemy->getStats().getHP()) / enemy->getStats().getMaxHP();
    enemyHPBar.setSize(sf::Vector2f(200.f * enemyHPPercent, 20.f));

}

void BattleState::playerAttack() {
    int damage = std::max(0, player.getStats().getAttack() - enemy->getStats().getDefense());
    int newHP = enemy->getStats().getHP() - damage;
    enemy->getStats().setHP(std::max(0, newHP));
    infoText.setString("You hit " + enemy->getStats().getName() + " for " + std::to_string(damage) + " damage!");
}

void BattleState::enemyAttack() {
    int damage = std::max(0, enemy->getStats().getAttack() - player.getStats().getDefense());
    int newHP = player.getStats().getHP() - damage;
    player.getStats().setHP(std::max(0, newHP));
    infoText.setString(enemy->getStats().getName() + " hits you for " + std::to_string(damage) + " damage!");
}
