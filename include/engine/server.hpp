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

#include <SDL2/SDL_net.h>
#include <vector>
#include <cstdio>

#include <engine/player.hpp>


class Player; // Forward declaration of Player

class Server {
private:
    IPaddress ip;                   // Server IP address
    TCPsocket serverSocket;         // Server TCP socket
    std::vector<TCPsocket> clients; // List of connected clients
    Player* player;                 // Pointer to the single player in the game
    int currentControllerId;        // ID of the client with control

    void broadcastGameState();

public:
    Server(Uint16 port, Player* player);
    ~Server();

    void acceptClients();
    void processClientActions();
    void update();
};
