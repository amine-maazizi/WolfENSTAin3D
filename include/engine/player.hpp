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
#include <stdbool.h>

class Player : public Camera {
public:

    Player();

    void damage(float);

    float life;
    bool isAlive;
};

