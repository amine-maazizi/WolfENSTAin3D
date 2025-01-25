/**
 * @file        game_scene.hpp
 * @brief       fichier entête qui comporte les elements de la scène du jeu
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
#include <engine/enemy.hpp>
#include <engine/map.hpp>
#include <engine/gui.hpp>
#include <engine/minimap.hpp>
#include <engine/effects.hpp>

#include <engine/server.hpp>
#include <engine/client.hpp>

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * @file        game_scene.hpp
 * @brief       Header for game scene elements, including server-client networking.
 * @author      Amine Maazizi
 * @date        2025-01-23
 * @version     1.1
 * 
 * @details
 * This class manages the core gameplay loop, including rendering, input handling,
 * and networking for multiplayer modes (host or join).
 */

#pragma once

#include <engine/scene.hpp>
#include <engine/player.hpp>
#include <engine/constantes.hpp>
#include <engine/raycaster.hpp>
#include <engine/billboard_manager.hpp>
#include <engine/enemy.hpp>
#include <engine/map.hpp>
#include <engine/gui.hpp>
#include <engine/minimap.hpp>
#include <engine/effects.hpp>

#include <engine/server.hpp>
#include <engine/client.hpp>

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class GameScene : public Scene {
private:
    Server server;  
    Client client;  

public:
    // Mon engin de raycasting
    Player player;
    SDL_Texture* buffTex;
    Raycaster raycaster;
    std::vector<Enemy> enemies;
    BillboardManager bbManager;
    GUI* gui;
    Effects fx;
    bool help;

    GameScene(SDL_Window* window, SDL_Renderer* renderer);
    ~GameScene();

    // Core 
    int process(float dt);   
    void render(float dt);             
    int handleInput(const Uint8* keystate);         

    // Lifecycle management
    void onEnter();                  
    void onExit();                   
    void pause();                   
    void resume();                   
};
