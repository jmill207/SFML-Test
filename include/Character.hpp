#pragma once
#include <string>

class Character {
private:
    std::string name;
    int maxHP;
    int hp;
    int attack;
    int magic;
    int defense;
    int magicDef;
    int speed;

public:
    Character(std::string n, int hp, int atk, int mag, int def, int magDef, int spd)
        : name(std::move(n)),
          maxHP(hp), hp(hp),
          attack(atk), magic(mag),
          defense(def), magicDef(magDef),
          speed(spd)
    {}

    int& getHP() { return hp; } 
    void setHP(int h) { hp = h; }
    int getMaxHP() const { return maxHP; }
    int getAttack() const { return attack; }
    int getMagic() const { return magic; }
    int getDefense() const { return defense; }
    int getMagicDefense() const { return magicDef; }
    int getSpeed() const { return speed; }
    std::string getName() const { return name; }

    void takeDamage(int dmg) {
        hp = std::max(0, hp - dmg);
    }

    bool isDead() const { return hp <= 0; }
};
