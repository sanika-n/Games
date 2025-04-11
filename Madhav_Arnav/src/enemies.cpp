#include "enemy.h"
#include <iostream>

Enemy::Enemy(std::string name, int hp, int lane, int pos)
    : name(name), health(hp), lane(lane), position(pos) {}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
}

void Enemy::printStatus() const {
    std::cout << "Enemy " << name << " has " << health << " health, "
              << "at lane " << lane << " and position " << position << "."
              << std::endl;
}

void Enemy::move() {
    // Move one grid to the left if not already at the left edge.
    if (position > 0) {
        position--;
    } else {
        std::cout << name << " has reached the left edge!" << std::endl;
    }
}

std::string Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getLane() const {
    return lane;
}

int Enemy::getPosition() const {
    return position;
}
