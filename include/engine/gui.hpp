
/**
 * @file        gui.hpp
 * @brief       Class implémentant le Graphical User Interface du jeu
 * @author      Amine Maazizi
 * @date        2024-01-19
 * @version     1.0
 * 
 * @details
 *  Comporte
 * - Les vies
 * - Le niveau
 * - Le score
 * - L'icon du visage
 * - L'Ammo restant
 * 
 * @note
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <engine/constantes.hpp>
#include <engine/animated_sprite.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>

class GUI {
public:
    GUI(SDL_Renderer*);
    ~GUI();
    void render(float, int, int, int, int, int, bool);
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* fpsText;
    SDL_Surface* pannelSurf;
    SDL_Texture* pannelTex;
    AnimatedSprite character;
    AnimatedSprite gun;
    SDL_Texture* guiTex;
};