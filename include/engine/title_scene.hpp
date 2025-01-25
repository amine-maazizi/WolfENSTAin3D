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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class TitleScene : public Scene {
public:
    TitleScene(SDL_Window* window, SDL_Renderer* renderer);

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

    // Background image and text
    SDL_Surface* bgSurf;
    SDL_Texture* bgTex;
    TTF_Font* font;
    SDL_Surface* startTextSurf;
    SDL_Texture* startTextTex;

    // Text blinking
    float blinkTimer;
    bool showText;

    // Helper functions
    void loadAssets();
    void cleanUp();
};