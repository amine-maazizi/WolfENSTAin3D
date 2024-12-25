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

#include <engine/vector2D.hpp>
#include <engine/constantes.hpp>
#include <cmath> // For M_PI

class Camera {
public:
    Vector2D<double> position; // Camera's position in the world
    Vector2D<double> direction; // Camera's viewing direction
    Vector2D<double> plane; // Camera plane for FOV projection
    double moveSpeed; // Movement speed
    double rotSpeed; // Rotation speed

    Camera();
};

