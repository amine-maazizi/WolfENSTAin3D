/**
 * @file        billboard_manager.hpp
 * @brief       fichier entête de la classe qui va gérer le sorting, projection et rendering des billboard 
 * @author      Amine Maazizi
 * @date        2024-12-27
 * @version     1.0
 * 
 * @details
 * 
 *  
 * @note
 * J'utiliserais un vecteur pour stocker les billboard histoire que ça soit extensible pour un niveau générer de manière proceedurale.
 */

#pragma once

#include <engine/billboard.hpp>
#include <vector>


class BillboardManager {
    public:
        BillboardManager();
        void sortBillboards(std::vector<int>&, std::vector<double>&, int);
        std::vector<Billboard> billboards;
        std::vector<int> billboardOrder;
        std::vector<double> billboardDistance;
        std::vector<double> ZBuffer;
};