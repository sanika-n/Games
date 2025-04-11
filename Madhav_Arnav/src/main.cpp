#include <iostream>
#include "enemy.h"
#include "defender.h"
#include <vector>
#include <string>
#include <unordered_map>
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
    unordered_map<string, int> elixir_costs;
    elixir_costs["PeaShooter"] = 3;
    elixir_costs["BonkChoy"] = 5;

    int elixir = 0;
    bool gameOver = false;
    int turn = 0;

    while (!gameOver) {
        // Loopign through all defenders and calling their attack function
        for (int lane = 0; lane < lanes.size(); ++lane) {
            for (int pos = 0; pos < lanes[lane].size(); ++pos) {
                Defender* def = lanes[lane][pos];
                if (def != nullptr) {
                    def->attack(all_enemies);
                }
            }
        }
        
        // Spawing a new enemy
        if (randint(1,5)==5) {
            all_enemies.push_back(new Enemy("Goblin", 100, randint(0, 2), 9+1));
        }


        // Moving all Enemies
        cout << "Elixir: " << elixir << endl;
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



        // Printing the Board
        cout << "============================" << endl;
        cout << "Turn " << turn << ":" << endl;

        for (size_t lane = 0; lane < lanes.size(); lane++) {
            cout << "Lane " << lane + 1 << ": ";
            for (size_t grid = 0; grid < lanes[lane].size(); grid++) {
                // Check if this cell matches the enemy's position.
                bool enemy_in_sq = false;
                for (Enemy* enemy : all_enemies) {
                    if ((lane == static_cast<size_t>(enemy->getLane())) && (grid == static_cast<size_t>(enemy->getPosition()))) {
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
                string type;
                iss >> type >> lane_number >> pos;
                if (elixir_costs.find(type) != elixir_costs.end()) {
                    if (elixir_costs[type] > elixir) {
                        cout << "Not enough elixir. Passing turn" << endl;
                    }
                    else {
                        lanes[lane_number-1][pos] = new Defender(type, lane_number-1, pos);
                        elixir -= elixir_costs[type];
                    }

                }
                else {
                    cout << "Invalid defender type. Passing turn" << endl;
                }
            } 
            else {
                cout << "Invalid command. Passing turn. Please enter 'p' or 's'" << endl;
            }
            turn++;
            elixir++;
            if (elixir > 10) {
                elixir = 10;
            }
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
