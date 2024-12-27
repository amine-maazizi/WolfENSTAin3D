#include <engine/billboard_manager.hpp>

BillboardManager::BillboardManager(Camera& cam) {
    // id 7 --> chapoutout 
    billboards.push_back(Billboard(18.5, 10.5, 7));
    billboards.push_back(Billboard(18.5, 11.5, 7));
    billboards.push_back(Billboard(18.5, 12.5, 7));

    number = billboards.size();

    for (int i=0; i < number; i++) {
        billboardOrder.push_back(i);
        billboardDistance.push_back(
           (cam.position - billboards[i].position).getLength()
        );
    }

    sortBillboards();
}

void BillboardManager::sortBillboards() {
    // TO BE WRITTEN
}