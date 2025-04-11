#include <iostream>
#include "enemy.h"
#include "defender.h"

int main() {
    Enemy goblin("Goblin", 100);
    Defender archer("Archer", 30);

    archer.attack(goblin);
    goblin.printStatus();

    return 0;
}
