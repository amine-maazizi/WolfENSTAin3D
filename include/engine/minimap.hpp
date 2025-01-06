/**
 * @file        minimap.hpp
 * @brief       fichier entête qui gère le rendering de la minimap
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 * 
 * @note
 */

#pragma once

#include <SDL2/SDL.h>
#include <engine/camera.hpp>
#include <engine/constantes.hpp>

class Minimap {
    public:
        Minimap() = delete;
        static void render(SDL_Renderer*, Camera&, int[MAP_HEIGHT][MAP_WIDTH]);
};