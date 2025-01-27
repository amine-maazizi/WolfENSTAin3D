/**
 * @file        client.hpp
 * @brief       Header file defining the client side of the LAN system.
 * @author      Amine Maazizi
 * @date        2025-01-25
 * @version     1.0
 * 
 * @details
 * The Client class sends input actions to the server 
 * and receives updates about the game state.
 */

#pragma once

#include <SDL2/SDL_net.h>
#include <SDL2/SDL.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>

#include <engine/constantes.hpp>

class Client {
private:
    TCPsocket clientSocket;

public:
    Client();
    ~Client();

    bool connectToServer(const std::string &host, Uint16 port);
    void sendMessage(const std::string &message);
    std::string receiveMessage();
    void disconnect();

    void sendControlTransfer();
    void sendPlayerInput(Uint8 inputState);
    void sendEnemyDeath(int enemyID);

};