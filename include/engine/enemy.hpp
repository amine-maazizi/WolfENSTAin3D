/**
 * @file        enemy.hpp
 * @brief       fichier entête qui definit un enemie 
 * @author      Amine Maazizi
 * @date        2025-01-13
 * @version     1.0
 * 
 * @details
 * - Les enemies pour le moment vont essayer de se rapprocher du joueur suivant un algorithm de path finding A*
 *  
 * @note
 * 
 */

#pragma once

#include <engine/billboard.hpp>
#include <engine/constantes.hpp>
#include <engine/player.hpp>
#include <engine/effects.hpp>
#include <engine/a_star.hpp>


#include<memory>
#include <stdbool.h>

class Player;
class Enemy {
public:
    Enemy(Vector2D<double>, int);
    Enemy(double, double, int);  
    void moveEnemy(Player&, int[MAP_HEIGHT][MAP_WIDTH], Effects& fx, float);  
    void damage(float, Effects& fx);

    std::shared_ptr<Billboard> bb; 
    float health;
    bool isAlive;
private:
    Vector2D<double> velocity;
    float cooldown;
};
