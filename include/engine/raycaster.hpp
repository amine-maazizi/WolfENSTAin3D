/**
 * @file        raycaster.hpp
 * @brief       fichier entête du moteur du raycasting 
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 * cette classe se chargera de lancer l'algorithme de raycasting 
 * 
 * @note
 * 
 * 
 */

#pragma once

#include <engine/camera.hpp>
#include <engine/constantes.hpp>
#include <cmath>
#include <SDL2/SDL.h>
#include <stdbool.h>

class Raycaster {
    public:
        Raycaster() = delete;
        static void raycast(Camera&, int[][24], SDL_Renderer*);
};