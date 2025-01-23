/**
 * @file        player.hpp
 * @brief       fichier entête du joueur 
 * @author      Amine Maazizi
 * @date        2024-01-20
 * @version     1.0
 * 
 * @details
 * 
 * @note
 * 
 * 
 */


#pragma once

#include <SDL2/SDL.h>
#include <engine/camera.hpp>
#include <engine/billboard_manager.hpp>
#include <stdbool.h>
#include <cmath>

class BillboardManager;
class Effects;
class Player : public Camera {
public:
    Player(Effects& fx);

    void damage(float);
    void shoot(float, BillboardManager&);
    void process(int[][MAP_WIDTH], BillboardManager&);

    Effects& fx;
    int lives;
    float health;
    bool isAlive;
    float cooldown;
    int score;
    int ammo;
};

