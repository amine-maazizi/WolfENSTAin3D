/**
 * @file        sandbox_scene.hpp
 * @brief       fichier entête pour la scene qui servira à tester des choses atypique au jeu 
 * @author      Amine Maazizi
 * @date        2025-01-26
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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class SandboxScene : public Scene {
public:
    SandboxScene(SDL_Window* window, SDL_Renderer* renderer);

    // Core functions
    int process(float dt);
    void render(float dt);
    int handleInput(const Uint8* keystate);

    // Lifecycle management
    void onEnter();
    void onExit();
    void pause();
    void resume();


    void saveCurrentFrameAsPNG(const std::string&);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* bgMusic;

    Player player;
    Effects fx;
    std::vector<Enemy> enemies;
    BillboardManager bbManager;
    SDL_Texture* buffTex;
    Raycaster raycaster;

    // Helper functions
    void loadAssets();
    void cleanUp();
};