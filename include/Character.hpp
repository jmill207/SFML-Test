#pragma once
#include <string>
#include <algorithm>

class Character {
private:
    std::string name;
    int maxHP, hp, attack, magic, defense, magicDef, speed;
public:
    Character(std::string n, int hp, int atk, int mag, int def, int magD, int spd)
        : name(n), maxHP(hp), hp(hp), attack(atk), magic(mag),
          defense(def), magicDef(magD), speed(spd) {}

    int& getHP() { return hp; }
    void setHP(int h) { hp = h; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    std::string getName() const { return name; }

    void takeDamage(int dmg) { hp = std::max(0, hp - dmg); }
    bool isDead() const { return hp <= 0; }
};