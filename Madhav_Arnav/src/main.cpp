#include <iostream>
#include "enemy.h"
#include "defender.h"
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <random>

using namespace std;


int randint(int x, int y) {
    std::random_device rd;                      // Seed
    std::mt19937 gen(rd());                     // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(x, y); // Range: 1 to 3
    int randomNumber = dist(gen);
    return randomNumber;
}



int main() {
    vector<vector<Defender*>> lanes(3, vector<Defender*>(10, nullptr));
    vector<Enemy*> all_enemies;    

    bool gameOver = false;
    int turn = 0;

    while (!gameOver) {
        // Moving all Enemies
        for (Enemy* enemy : all_enemies) {
            enemy->move();
            if (enemy->getPosition() == 0) {
                cout << enemy->getName() << " has reached your house!" << endl;
                gameOver = true;
                break;
            }
            else {
                enemy->printStatus();
            }
        }

        // Spawing a new enemy
        if (randint(1,5)==5) {
            all_enemies.push_back(new Enemy("Goblin", 100, randint(1, 3), 9));
        }


        // Loopign through all defenders and calling their attack function

        

        // Printing the Board
        cout << "============================" << endl;
        cout << "Turn " << turn << ":" << endl;

        for (size_t lane = 0; lane < lanes.size(); lane++) {
            cout << "Lane " << lane + 1 << ": ";
            for (size_t grid = 0; grid < lanes[lane].size(); grid++) {
                // Check if this cell matches the enemy's position.
                bool enemy_in_sq = false;
                for (Enemy* enemy : all_enemies) {
                    if ((lane == static_cast<size_t>(enemy->getLane() - 1)) && (grid == static_cast<size_t>(enemy->getPosition()))) {
                        cout << "[G]";
                        enemy_in_sq = true;
                    }
                }
                if (!enemy_in_sq) {
                    if (lanes[lane][grid]) {
                        cout << "[D]";
                    } else {
                        cout << "[ ]";
                    }
                }

            }
            cout << endl;
        }
        cout << "============================" << endl;

        


        // Taking user input
        if (!gameOver) {
            string input;
            cout << "\n>>>";
            getline(cin, input);
        
            istringstream iss(input);
            string command;
            iss >> command;
        
            if (command == "p") {
                // Does Nothing
            } 
            else if (command == "s") {
                int lane_number, pos;
                iss >> lane_number >> pos;
                lanes[lane_number-1][pos] = new Defender("Archer", 10);
            } 
            else {
                cout << "Invalid command. Please enter 'p' or 's lane_number pos'." << endl;
            }
            turn++;
        }

    }

    // Clean up dynamically allocated memory
    for (auto &lane : lanes) {
        for (auto defender : lane) {
            if (defender != nullptr) {
                delete defender;
            }
        }
    }
    for (Enemy* e : all_enemies) {
        delete e;
    }

    return 0;
}