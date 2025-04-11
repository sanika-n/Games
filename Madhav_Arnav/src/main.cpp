#include <iostream>
#include "enemy.h"
#include "defender.h"
#include <vector>
#include <string>
#include <limits>

using namespace std;

int main() {
    vector<vector<Defender*>> lanes(3, vector<Defender*>(10, nullptr));

    Enemy goblin("Goblin", 100, 1, 9);

    bool gameOver = false;
    int turn = 0;

    while (!gameOver) {
        cout << "============================" << endl;
        cout << "Turn " << turn << ":" << endl;

        for (size_t lane = 0; lane < lanes.size(); lane++) {
            cout << "Lane " << lane + 1 << ": ";
            for (size_t grid = 0; grid < lanes[lane].size(); grid++) {
                // Check if this cell matches the enemy's position.
                if ((lane == static_cast<size_t>(goblin.getLane() - 1)) && (grid == static_cast<size_t>(goblin.getPosition()))) {
                    cout << "[G]";
                } else if (lanes[lane][grid]) {
                    cout << "[D]";
                } else {
                    cout << "[ ]";
                }
            }
            cout << endl;
        }
        cout << "============================" << endl;

        goblin.printStatus();

        // Optional gameplay logic:
        // For instance, if a defender occupies the enemy's current cell, let the defender attack.
        int enemyLaneIndex = goblin.getLane() - 1; // Adjust to 0-index for lanes vector.
        int enemyPos = goblin.getPosition();
        if (enemyLaneIndex >= 0 && enemyLaneIndex < static_cast<int>(lanes.size()) &&
            enemyPos >= 0 && enemyPos < static_cast<int>(lanes[enemyLaneIndex].size())) {
            if (lanes[enemyLaneIndex][enemyPos]) {
                cout << lanes[enemyLaneIndex][enemyPos]->getName() << " attacks " 
                     << goblin.getName() << "!" << endl;
                lanes[enemyLaneIndex][enemyPos]->attack(goblin);
            } else {
                cout << "No defender at the goblin's position." << endl;
            }
        }

        goblin.move();

        // End game condition: When the goblin reaches the leftmost grid (position 0).
        if (goblin.getPosition() == 0) {
            cout << goblin.getName() << " has reached your house! Game Over!" << endl;
            gameOver = true;
        }

        // Wait for user input before proceeding to the next turn.
        cout << "\nPress Enter to continue to the next turn..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        turn++;
    }

    // Clean up dynamically allocated memory for defenders.
    for (auto &lane : lanes) {
        for (auto defender : lane) {
            if (defender != nullptr) {
                delete defender;
            }
        }
    }

    return 0;
}
