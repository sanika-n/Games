#include <iostream>
#include <vector>
#include <limits>
#include "defender.h"

Defender::Defender(std::string type, int lane, int position)
    : type(type), lane(lane), position(position) {
    if (type == "PeaShooter") {
        attackPower = 20;
        range = 100;
    } else if (type == "BonkChoy") {
        attackPower = 35;
        range = 3;
    } else {
        std::cerr << "Unknown defender type: " << type << std::endl;
        attackPower = 10;
        range = 1;
    }
}


void Defender::attack(std::vector<Enemy*>& enemies) const {
    int targetIndex = -1;
    int closestDistance = std::numeric_limits<int>::max();

    // Loop to find the closest enemy in same lane and within range
    for (size_t i = 0; i < enemies.size(); ++i) {
        Enemy* enemy = enemies[i];

        if (enemy->getLane() != lane) continue;  // Skip enemies not in the same lane

        int distance = std::abs(enemy->getPosition() - position);
        if (distance <= range && distance < closestDistance) {
            closestDistance = distance;
            targetIndex = static_cast<int>(i);
        }
    }

    // If a target is found, attack
    if (targetIndex != -1) {
        Enemy* target = enemies[targetIndex];
        std::cout << type << " at position " << position
                  << " attacks enemy at position " << target->getPosition()
                  << " in lane " << lane + 1
                  << " for " << attackPower << " damage!" << std::endl;

        target->takeDamage(attackPower);

        // If enemy is dead, remove it
        if (target->getHealth() <= 0) {
            std::cout << "Enemy at position " << target->getPosition()
                      << " defeated by " << type << "!" << std::endl;

            // Remove enemy from vector
            for (size_t j = targetIndex + 1; j < enemies.size(); ++j) {
                enemies[j - 1] = enemies[j];
            }
            enemies.pop_back();
        }

    } else {
        std::cout << type << " at position " << position
                  << " found no enemy in range on lane " << lane << "." << std::endl;
    }
}
