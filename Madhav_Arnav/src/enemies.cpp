#include "enemy.h"
#include <iostream>

Enemy::Enemy(std::string name, int hp, int lane, int pos)
    : name(name), health(hp), lane(lane), position(pos) {}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
}

void Enemy::printStatus() const {
    std::cout << "Enemy " << name << " has " << health << " health, "
              << "at lane " << lane+1 << " and position " << position << "."
              << std::endl;
}

void Enemy::move() {
    position--;
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
