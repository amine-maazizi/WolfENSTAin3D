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
#include <vector>

#include <engine/player.hpp>
#include <engine/constantes.hpp>
#include <engine/raycaster.hpp>
#include <engine/billboard_manager.hpp>
#include <engine/map.hpp>
#include <engine/gui.hpp>
#include <engine/minimap.hpp>
#include <engine/effects.hpp>

class Application {
    private:
        // Essentielle SDL2
        SDL_Renderer* renderer;
        SDL_Window* window;

        // Mon engin de raycasting
        Player player;
        SDL_Texture* buffTex;
        Raycaster raycaster;
        BillboardManager bbManager;
        GUI* gui;
        Effects fx;
    public:
        Application();
        ~Application();

        void handleInput();
        void process();
        void render(float);
        void run();
};