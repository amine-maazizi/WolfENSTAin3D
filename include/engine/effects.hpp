
/**
 * @file        effects.hpp
 * @brief       Class qui regroupe les effets spéciaux qui seront utilisé dans le jeux
 * @author      Amine Maazizi
 * @date        2024-01-19
 * @version     1.0
 * 
 * @details
 * - Screen shake
 * - Teinture de l'écran
 * 
 * @note
 */

#pragma once

#include <SDL2/SDL.h>
#include <random>


//TODO: faire une structure qui regroupe les duration, mag et elapsed pour chaque effets pour pouvoir les fiare en parallele

class Effects {
    public:
        Effects();
        void shakeScreen(int, int);
        void applyScreenShake(SDL_Renderer*, SDL_Rect*);
    private:
        // Effects
        int duration; 
        int magnitude; 
        int elapsed;  

        // randomness
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<> dist;
};