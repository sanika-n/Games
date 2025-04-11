#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(std::string name, int hp);
    void takeDamage(int dmg);
    void printStatus() const;

private:
    std::string name;
    int health;
};

#endif // ENEMY_H
