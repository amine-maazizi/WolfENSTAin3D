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
#include <engine/map.hpp>
#include <engine/billboard_manager.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <stdbool.h>
#include <cassert>
#include <vector>

class Raycaster {
    private:
        // Map, Floor, Ceilling
        Uint32* buffer;
        std::vector<int> texture[TEXTURE_NUMBER];
    public:
        Raycaster(Camera&);
        ~Raycaster();
        void cast_rays(Camera&, int[MAP_HEIGHT][MAP_WIDTH], BillboardManager&); // TODO: vue que j'ai passer la camera dans le constructeur pas besoin de la redefinir commme arg de func
        void render(SDL_Renderer*, SDL_Texture*);
};