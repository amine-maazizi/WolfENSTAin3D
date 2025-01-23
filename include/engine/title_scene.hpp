/**
 * @file        title.hpp
 * @brief       fichier entête qui comporte les elements de l'écran principale du jeu
 * @author      Amine Maazizi
 * @date        2025-01-23
 * @version     1.0
 * 
 * @details
*
 * @note
 */

#pragma once

#include<engine/scene.hpp>
#include <engine/player.hpp>
#include <engine/constantes.hpp>
#include <engine/raycaster.hpp>
#include <engine/billboard_manager.hpp>
#include <engine/map.hpp>
#include <engine/gui.hpp>
#include <engine/minimap.hpp>
#include <engine/effects.hpp>

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class TitleScene : public Scene {
public:
    // Mon engin de raycasting
    TitleScene(SDL_Window*, SDL_Renderer*);

    // Core 
    int process(float);   
    void render(float);             
    int handleInput(const Uint8*);         

    // Lifecycle management : À implemnter si besoin
    void onEnter();                  
    void onExit();                   
    void pause();                   
    void resume();                   
};
