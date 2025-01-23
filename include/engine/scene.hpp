/**
 * @file        scene.hpp
 * @brief       fichier entête qui comporte le système de gestion de scènes
 * @author      Amine Maazizi
 * @date        2025-01-23
 * @version     1.0
 * 
 * @details
*
 * @note
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <engine/constantes.hpp>

class Scene {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* bgMusic;

    // Core 
    virtual int process(float) = 0;   
    virtual void render(float) = 0;             
    virtual int handleInput(const Uint8*) = 0;         

    // Lifecycle management : À implemnter si besoin
    virtual void onEnter() = 0;                  
    virtual void onExit() = 0;                   
    virtual void pause() = 0;                   
    virtual void resume() = 0;                   
};


