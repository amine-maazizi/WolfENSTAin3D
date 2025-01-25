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
#include <vector>
#include <cstdio>

class Client {
private:
    IPaddress ip;      // Server IP address
    TCPsocket socket;  // Client's socket connection
    float playerX, playerY; // Player position

public:
    bool isController; // True if this client has control

    Client(const char* serverIP, Uint16 port);
    ~Client();

    void sendInput(Uint8 actionType, float x = 0, float y = 0);
    void receiveGameState();
    void requestControlTransfer();
    void render();
};
