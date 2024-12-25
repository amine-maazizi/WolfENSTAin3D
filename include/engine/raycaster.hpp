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
#include <SDL2/SDL.h>
#include <cmath>
#include <stdbool.h>
#include <map>
#include <tuple>

using Distance = double;
using Color = SDL_Color;
using MapData = std::tuple<Color, Distance>;

class Raycaster {
    private:
        std::map<int, MapData> dataMap;
    public:
        Raycaster();
        void cast_rays(Camera&, int[][MAP_WIDTH]);
        void render(SDL_Renderer*);
};