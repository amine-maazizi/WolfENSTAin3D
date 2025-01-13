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
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include <engine/camera.hpp>
#include <engine/constantes.hpp>
#include <engine/raycaster.hpp>
#include <engine/billboard_manager.hpp>
#include <engine/map.hpp>
#include <engine/minimap.hpp>

class Application {
    private:
        // Essentielle SDL2
        SDL_Renderer* renderer;
        SDL_Window* window;

        // Mon engin de raycasting
        Camera camera;
        SDL_Texture* buffTex;
        Raycaster raycaster;
        BillboardManager bbManager;

        // Affichage du text
        TTF_Font* font;
        SDL_Surface* gui;
    public:
        Application();
        ~Application();

        void handleInput();
        void process();
        void render(float);
        void run();
};