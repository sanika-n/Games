#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(std::string name, int hp, int lane, int pos);

    void takeDamage(int dmg);
    void printStatus() const;
    void move();

    std::string getName() const;
    int getHealth() const;
    int getLane() const;
    int getPosition() const;

private:
    std::string name;
    int health;
    int lane;     // (1, 2, or 3).
    int position; // (0-9)
};

#endif
