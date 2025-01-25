/**
 * @file        select_scene.hpp
 * @brief       fichier entête qui comporte les elements de l'écran de selection
 * @author      Amine Maazizi
 * @date        2025-01-25
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
#include <engine/game_scene.hpp>

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


class SelectScene : public Scene {
public:
    SelectScene(SDL_Window* window, SDL_Renderer* renderer);

    // Core functions
    int process(float dt);
    void render(float dt);
    int handleInput(const Uint8* keystate);

    // Lifecycle management
    void onEnter();
    void onExit();
    void pause();
    void resume();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* bgMusic;

    // Menu options
    TTF_Font* font;
    std::vector<std::string> menuOptions;
    int selectedOption; // Index of the currently selected option
    bool isKeyPressed;

    // Text blinking
    float blinkTimer;
    bool showText;

    // Helper functions
    void loadAssets();
    void cleanUp();
};