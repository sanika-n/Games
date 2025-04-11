#include <iostream>
#include "defender.h"

Defender::Defender(std::string type, int damage) : type(type), attackPower(damage) {}

void Defender::attack(Enemy& target) const {
    std::cout << "Defender of type " << type << " attacks enemy!" << std::endl;
    target.takeDamage(attackPower);
}
