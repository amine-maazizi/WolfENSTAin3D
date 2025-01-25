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
#include <engine/enemy.hpp>
#include <engine/camera.hpp>
#include <engine/player.hpp>
#include <engine/effects.hpp>

#include <vector>
#include <memory>  // For smart pointers
#include <algorithm>


class Player;
class Enemy;
class BillboardManager {
    public:
        BillboardManager(Camera&, Effects& fx);
        void sortBillboards();
        void addBillboard(std::shared_ptr<Billboard>, Camera&);

        Effects& fx;

        int number;
        std::vector<std::shared_ptr<Billboard>> billboards;  // Change unique_ptr to shared_ptr
        std::vector<Enemy> enemies;
        std::vector<int> billboardOrder;
        std::vector<double> billboardDistance;
        std::vector<double> ZBuffer;
};
