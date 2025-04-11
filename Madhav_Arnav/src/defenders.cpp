#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "defender.h"

Defender::Defender(std::string type, int damage, int range)
    : type(type), attackPower(damage), range(range) {}

void Defender::attack(std::vector<Enemy*> enemies) const {
    Enemy* closest = nullptr;
    int minPosition = std::numeric_limits<int>::max();

    for (Enemy* enemy : enemies) {
        int pos = enemy->getPosition();
        if (pos < minPosition) {
            minPosition = pos;
            closest = enemy;
        }
    }

    if (closest && minPosition <= range) {
        std::cout << type << " attacks enemy at position " << minPosition
                  << " for " << attackPower << " damage!" << std::endl;
        closest->takeDamage(attackPower);
    } else {
        std::cout << type << " found no enemies in range." << std::endl;
    }
}

std::string Defender::getName() const {
    return type;
}

int Defender::getRange() const {
    return range;
}

void removeDeadEnemies(std::vector<Enemy*>& enemies) {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                       [](Enemy* enemy) {
                           return enemy->getHealth() <= 0;
                       }),
        enemies.end()
    );
}
