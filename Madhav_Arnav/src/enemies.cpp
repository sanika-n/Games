#include <iostream>
#include "enemy.h"

Enemy::Enemy(std::string name, int hp) : name(name), health(hp) {}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Enemy::printStatus() const {
    std::cout << "Enemy " << name << " has " << health << " HP left." << std::endl;
}
