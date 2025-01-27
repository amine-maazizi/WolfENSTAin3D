#include <engine/server.hpp>

Server::Server() : serverSocket(nullptr), isRunning(false) {}

Server::~Server() {
    stop();
}

bool Server::start(Uint16 port) {
    if (SDLNet_Init() == -1) {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return false;
    }

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, nullptr, port) == -1) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        return false;
    }

    serverSocket = SDLNet_TCP_Open(&ip);
    if (!serverSocket) {
        std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void Server::stop() {
    for (auto &client : clients) {
        SDLNet_TCP_Close(client);
    }
    if (serverSocket) {
        SDLNet_TCP_Close(serverSocket);
    }
    SDLNet_Quit();
    isRunning = false;
}

void Server::broadcast(const std::string &message) {
    for (auto &client : clients) {
        SDLNet_TCP_Send(client, message.c_str(), message.size() + 1);
    }
}

std::vector<std::string> Server::receiveMessages() {
    std::vector<std::string> messages;
    if (!serverSocket) return messages;

    TCPsocket newClient = SDLNet_TCP_Accept(serverSocket);
    if (newClient) {
        clients.push_back(newClient);
    }

    for (auto &client : clients) {
        char buffer[1024];
        int len = SDLNet_TCP_Recv(client, buffer, sizeof(buffer));
        if (len > 0) {
            messages.push_back(std::string(buffer, len));
        }
    }

    return messages;
}

void Server::sendControlTransfer() {
    broadcast(std::string(1, CONTROL_TRANSFER));
}

void Server::sendPlayerInput(Uint8 inputState) {
    broadcast(std::string(1, PLAYER_INPUT) + std::string(1, inputState));
}

void Server::sendEnemyDeath(int enemyID) {
    broadcast(std::string(1, ENEMY_DEAD) + std::to_string(enemyID));
}
