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
#include <SDL2/SDL_image.h>
#include <iostream>
#include <engine/camera.hpp>
#include <engine/constantes.hpp>
#include <engine/raycaster.hpp>
#include <engine/map.hpp>

class Application {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        Camera camera;
        SDL_Texture* buffTex;
        Raycaster raycaster;
    public:
        Application();
        ~Application();

        void handleInput();
        void process();
        void render();
        void run();
};