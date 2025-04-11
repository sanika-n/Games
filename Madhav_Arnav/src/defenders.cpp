#include <iostream>
#include <vector>
#include <limits>
#include "defender.h"

Defender::Defender(std::string type, int lane, int position)
    : type(type), lane(lane), position(position) {
    if (type == "PeaShooter") {
        attackPower = 20;
        range = 5;
    } else if (type == "BonkChoy") {
        attackPower = 35;
        range = 1;
    } else {
        std::cerr << "Unknown defender type: " << type << std::endl;
        attackPower = 10;
        range = 1;
    }
}


void Defender::attack(std::vector<Enemy*>& enemies) const {
    int closestDist = std::numeric_limits<int>::max();
    int targetIndex = -1;

    for (size_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->getLane() != lane) continue;

        int dist = std::abs(enemies[i]->getPosition() - position);
        if (dist <= range && dist < closestDist) {
            closestDist = dist;
            targetIndex = static_cast<int>(i);
        }
    }

    if (targetIndex != -1) {
        Enemy* target = enemies[targetIndex];
        std::cout << type << " at pos " << position
                  << " attacks enemy at pos " << target->getPosition()
                  << " for " << attackPower << " damage!" << std::endl;

        target->takeDamage(attackPower);

        if (target->getHealth() <= 0) {
            std::cout << "Enemy defeated by " << type << "!" << std::endl;

            // delete target; // if dynamic
            for (size_t j = targetIndex + 1; j < enemies.size(); ++j) {
                enemies[j - 1] = enemies[j];
            }
            enemies.pop_back();
        }
    } else {
        std::cout << type << " found no enemies in range on lane " << lane << "." << std::endl;
    }
}
