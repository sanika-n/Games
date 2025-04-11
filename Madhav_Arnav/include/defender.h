#ifndef DEFENDER_H
#define DEFENDER_H

#include <string>
#include "enemy.h"

class Defender {
public:
    Defender(std::string type, int damage);
    void attack(Enemy& target) const;

private:
    std::string type;
    int attackPower;
};

#endif // DEFENDER_H
