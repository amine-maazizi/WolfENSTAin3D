#include <engine/billboard_manager.hpp>

// Constructor: Use unique_ptr to store billboards and link them with enemies
BillboardManager::BillboardManager(Camera& cam) {
    // Initializing some billboards and enemies
    billboards.push_back(std::make_unique<Billboard>(18.5, 10.5, 7));
    enemies.push_back(Enemy(18.5, 11.5, 7));

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
void BillboardManager::processEnemies(Camera& cam, int map[MAP_WIDTH][MAP_HEIGHT]) {
    for (auto& e : enemies) {
        e.moveEnemy(cam, map);

        // Update the position of the corresponding billboard for each enemy
        // Assuming the billboard corresponds to the enemy's position
        for (auto& bb : billboards) {
            if (bb->texID == e.texID) {
                bb->position = e.position;
                break;  // Assuming one billboard per enemy
            }
        }
    }

    // After each frame, sort billboards based on their new positions
    sortBillboards();
}