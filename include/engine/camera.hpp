/**
 * @file        camera.hpp
 * @brief       fichier entête de la camera  
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 * 
 * @note
 * cette classe servira de classe de base pour l'entité joueur par la suite
 * 
 */

#pragma once

#include <SDL2/SDL.h>
#include <engine/vector2D.hpp>
#include <engine/constantes.hpp>
#include <cmath> // pour PI

class Camera {
public:
    Vector2D<double> position; 
    Vector2D<double> direction; 
    Vector2D<double> plane;

    double moveSpeed; 
    double rotSpeed; 

    Camera();
    void move(int[MAP_HEIGHT][MAP_WIDTH]);
};

