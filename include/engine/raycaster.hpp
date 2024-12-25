/**
 * @file        raycaster.hpp
 * @brief       fichier entête du moteur du raycasting 
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 * cette classe seraint static se chargera de lancer l'algorithme de raycasting 
 * 
 * @note
 * - raycasting basée sur DDA (Digital Differential Analysis)
 * - Je vais séparer la partie raycasting et rendering pour que le code reste cohérrent avec la logique de l'engin, mais les fusionner serait plus performant
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