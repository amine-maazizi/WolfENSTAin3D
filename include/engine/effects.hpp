
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

struct Effect {
        int duration; 
        int magnitude; 
        int elapsed;  
};


class Effects {
    public:
        Effects();
        void shakeScreen(int, int);
        void applyScreenShake(SDL_Renderer*, SDL_Rect*);
        
        void reden(int, int);
        void applyRedening(SDL_Renderer*);
    private:
        // Effects
        Effect screenShake;
        Effect redening;

        // randomness
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<> dist;
};