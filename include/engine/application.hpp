/**
 * @file        application.hpp
 * @brief       fichier entête de l'application 
 * @author      Amine Maazizi
 * @date        2024-12-23
 * @version     1.0
 * 
 * @details
 * regroupe l'engin de raycasting et le rendering
 * @note
 */

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <engine/constantes.hpp>
#include <engine/raycaster.hpp>
#include <engine/map.hpp>

class Application {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        Camera camera;
    
    public:
        Application();
        ~Application();

        void handleInput();
        void process();
        void render();
        void run();
};