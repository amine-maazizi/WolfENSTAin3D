#include <engine/billboard_manager.hpp>

BillboardManager::BillboardManager() {
    // id 7 --> chapoutout 
    billboards.push_back(Billboard(18.5, 10.5, 7));
    billboards.push_back(Billboard(18.5, 11.5, 7));
    billboards.push_back(Billboard(18.5, 12.5, 7));
}

void BillboardManager::sortBillboards(std::vector<int>& orders, std::vector<double>& disances, int amount) {
    // TO BE WRITTEN
}