#ifndef DEFENDER_H
#define DEFENDER_H

#include <string>
#include <vector>
#include "enemy.h"

class Defender {
public:
    Defender(std::string type, int lane, int position);

    int getPosition() const;

    void attack(std::vector<Enemy*>& enemies) const;

    std::string getName() const;
    int getRange() const;
    int getLane() const;

private:
    std::string type;
    int attackPower;
    int range;
    int lane;
    int position;

};

// Utility function to remove dead enemies (health <= 0)
void removeDeadEnemies(std::vector<Enemy*>& enemies);

#endif


// add type of defenders: pea shooter, bonk choy, etc.
// attack function takes the vector of pointers of enemies and it should find the closest enemy, and attacks it in one turn
// and attack it
// add kill function that will remove the enemy from the vector of pointers

