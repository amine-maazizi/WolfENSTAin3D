/**
 * @file        server.hpp
 * @brief       fichier entête qui comporte le coté serveur du LAN
 * @author      Amine Maazizi
 * @date        2025-01-25
 * @version     1.0
 * 
 * @details
* manages the game state (player positions, enemies, and actions) 
* and synchronizes data across all clients.
*
 * @note
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <vector>
#include <cstdio>

#include <iostream>
#include <string>

#include <engine/player.hpp>
#include <engine/constantes.hpp>



class Server {
private:
    TCPsocket serverSocket;
    std::vector<TCPsocket> clients;
    bool isRunning;

public:
    Server();
    ~Server();

    bool start(Uint16 port);
    void stop();
    void broadcast(const std::string &message);
    std::vector<std::string> receiveMessages();
    void sendControlTransfer();
    void sendPlayerInput(Uint8 inputState);
    void sendEnemyDeath(int enemyID);

};