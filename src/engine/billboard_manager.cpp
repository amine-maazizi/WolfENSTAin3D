#include <engine/billboard_manager.hpp>

BillboardManager::BillboardManager(Camera& cam) {
    // id 7 --> chapoutout 
    billboards.push_back(Billboard(18.5, 10.5, 7));
    billboards.push_back(Billboard(18.5, 11.5, 7));
    billboards.push_back(Billboard(18.5, 12.5, 7));
    billboards.push_back(Billboard(21.5, 1.5, 8));
    billboards.push_back(Billboard(15.5, 1.5, 8));
    billboards.push_back(Billboard(10.0, 15.1, 9));
    billboards.push_back(Billboard(10.5, 15.8, 9));

    number = billboards.size();

    for (int i=0; i < number; i++) {
        billboardOrder.push_back(i);
        billboardDistance.push_back(
           (cam.position - billboards[i].position).length()
        );
    }

    sortBillboards();
}

void BillboardManager::sortBillboards() {
    std::vector<std::pair<double, int>> bbs(number);
    for (int i = 0; i < number; i++) {
        bbs[i].first = billboardDistance[i];
        bbs[i].second = billboardOrder[i];
    }

    // Fonction de sort de la standarb lib
    std::sort(bbs.begin(), bbs.end());

    // restaurer l'ordre inverse : plus loins -> plus proche
    for (int i = 0; i < number; i++) {
        billboardDistance[i] = bbs[number - i - 1].first;
        billboardOrder[i] = bbs[number - i - 1].second;
    }
} 