#include <engine/billboard_manager.hpp>

// Constructor: Use unique_ptr to store billboards and link them with enemies
BillboardManager::BillboardManager(Camera& cam, Effects& fx): fx(fx) {
    // Initializing some billboards and enemies
    billboards.push_back(std::make_shared<Billboard>(2, 2, 7));
    billboards.push_back(std::make_shared<Billboard>(2, 3, 7));
    
    billboards.push_back(std::make_shared<Billboard>(7, 2, 8));
    billboards.push_back(std::make_shared<Billboard>(8, 2, 8));
    billboards.push_back(std::make_shared<Billboard>(2, 11, 8));
    billboards.push_back(std::make_shared<Billboard>(15, 11, 8));
    
    billboards.push_back(std::make_shared<Billboard>(2, 2, 9));
    billboards.push_back(std::make_shared<Billboard>(15, 2, 9));
    billboards.push_back(std::make_shared<Billboard>(2, 17, 9));
    billboards.push_back(std::make_shared<Billboard>(15, 17, 9));
    

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

void BillboardManager::addBillboard(std::shared_ptr<Billboard> bb, Camera& cam) {
    // Transfer ownership of the unique_ptr to the billboards vector
    billboards.push_back(std::move(bb));

    // Update metadata
    int newBillboardIndex = number;  // The index of the new billboard
    number++;
    billboardOrder.push_back(newBillboardIndex);
    billboardDistance.push_back((cam.position - billboards[newBillboardIndex]->position).length());

    // Re-sort the billboards
    sortBillboards();
}
