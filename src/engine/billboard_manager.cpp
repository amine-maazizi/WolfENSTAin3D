#include <engine/billboard_manager.hpp>

// Constructor: Use unique_ptr to store billboards and link them with enemies
BillboardManager::BillboardManager(Camera& cam) {
    // Initializing some billboards and enemies
    billboards.push_back(std::make_unique<Billboard>(5.5, 2, 7));
    billboards.push_back(std::make_unique<Billboard>(6, 3, 7));
    billboards.push_back(std::make_unique<Billboard>(6.5, 2, 7));
    billboards.push_back(std::make_unique<Billboard>(2, 17, 9));
    billboards.push_back(std::make_unique<Billboard>(3, 18, 9));
    billboards.push_back(std::make_unique<Billboard>(2, 19, 9));
    billboards.push_back(std::make_unique<Billboard>(2, 2, 8));
    billboards.push_back(std::make_unique<Billboard>(15, 31, 8));
    billboards.push_back(std::make_unique<Billboard>(2, 31, 8));
    billboards.push_back(std::make_unique<Billboard>(15, 2, 8));

    // Initialize enemies
    // enemies.push_back(Enemy(2.0, 10.0, 10));  // Enemy 1: Narrow corridor
    // enemies.push_back(Enemy(5.0, 8.0, 7));   // Enemy 2: Small room
    // enemies.push_back(Enemy(7.0, 20.0, 9));  // Enemy 3: Intersection
    // enemies.push_back(Enemy(8.0, 15.0, 9));  // Enemy 4: Mid-map
    // enemies.push_back(Enemy(9.0, 18.0, 9));  // Enemy 5: Central challenge
    // enemies.push_back(Enemy(10.0, 4.0, 7));  // Enemy 6: Guarding key items
    // enemies.push_back(Enemy(12.0, 6.0, 7));  // Enemy 7: Dead-end ambush
    // enemies.push_back(Enemy(13.0, 13.0, 9)); // Enemy 8: Room corner


    // Link enemies to billboards (optional: if you want a separate billboard for each enemy)
    for (auto& e : enemies) {
        billboards.push_back(std::make_unique<Billboard>(e.position, e.texID)); // Creating new billboards for each enemy
    }

    number = billboards.size();

    for (int i = 0; i < number; i++) {
        billboardOrder.push_back(i);
        billboardDistance.push_back(
           (cam.position - billboards[i]->position).length()
        );
    }

    sortBillboards();
}

// Sorting function (sorting based on the distance to the camera)
void BillboardManager::sortBillboards() {
    std::vector<std::pair<double, int>> bbs(number);
    for (int i = 0; i < number; i++) {
        bbs[i].first = billboardDistance[i];
        bbs[i].second = billboardOrder[i];
    }

    std::sort(bbs.begin(), bbs.end());

    for (int i = 0; i < number; i++) {
        billboardDistance[i] = bbs[number - i - 1].first;
        billboardOrder[i] = bbs[number - i - 1].second;
    }
}

// Append new billboards
void BillboardManager::appendBillboards(std::vector<Billboard*> bbs, Camera& cam) {
    for (auto* bb : bbs) {
        billboards.push_back(std::make_unique<Billboard>(*bb));  // Creating unique_ptr for each new billboard
    }

    int start = number - 1;
    number += bbs.size();

    for (int i = start; i < number; i++) {
        billboardOrder.push_back(i);
        billboardDistance.push_back(
           (cam.position - billboards[i]->position).length()
        );
    }

    sortBillboards();
}

// Process enemy movements and update corresponding billboard positions
void BillboardManager::processEnemies(Player& p, int map[MAP_HEIGHT][MAP_WIDTH], Effects& fx) {
    // Track indices of billboards to remove
    std::vector<int> billboardsToRemove;

    // Process enemies and mark billboards for removal if enemies are not alive
    for (size_t i = 0; i < enemies.size(); ++i) {
        Enemy& e = enemies[i];
        e.moveEnemy(p, map, fx);

        // Update the position of the corresponding billboard for each enemy
        for (size_t j = 0; j < billboards.size(); ++j) {
            if (billboards[j]->texID == e.texID) {
                if (!e.isAlive) {
                    billboardsToRemove.push_back(j);  // Mark billboard for removal
                } else {
                    billboards[j]->position = e.position;  // Update position
                }
                break;
            }
        }
    }

    // Remove enemies that are not alive
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
            return !e.isAlive;
        }),
        enemies.end()
    );

    // Remove marked billboards
    for (auto it = billboardsToRemove.rbegin(); it != billboardsToRemove.rend(); ++it) {
        int index = *it;
        billboards.erase(billboards.begin() + index);
        billboardOrder.erase(billboardOrder.begin() + index);
        billboardDistance.erase(billboardDistance.begin() + index);
    }

    // Update the number of billboards and sort based on the new state
    number = billboards.size();
    sortBillboards();
}
