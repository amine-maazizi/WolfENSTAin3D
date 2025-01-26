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
#include <SDL2/SDL_mixer.h>

#include <vector>

#include <engine/title_scene.hpp>
#include <engine/game_scene.hpp>
#include <engine/select_scene.hpp>
#include <engine/sandbox_scene.hpp>



class Application {
    private:
        // Essentielle SDL2
        SDL_Renderer* renderer;
        SDL_Window* window;

        // Scenes
        int currentScene;
        Scene* scenes[4];
    public:
        Application();
        ~Application();

        void handleInput();
        void process(float);
        void render(float);
        void run();
};