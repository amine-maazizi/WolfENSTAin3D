#include <engine/client.hpp>


Client::Client() : clientSocket(nullptr) {}

Client::~Client() {
    disconnect();
}

bool Client::connectToServer(const std::string &host, Uint16 port) {
    if (SDLNet_Init() == -1) {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
        return false;
    }

    IPaddress ip;
    if (SDLNet_ResolveHost(&ip, host.c_str(), port) == -1) {
        std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
        return false;
    }

    clientSocket = SDLNet_TCP_Open(&ip);
    if (!clientSocket) {
        std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
        return false;
    }

    return true;
}

void Client::sendMessage(const std::string &message) {
    if (clientSocket) {
        SDLNet_TCP_Send(clientSocket, message.c_str(), message.size() + 1);
    }
}

std::string Client::receiveMessage() {
    char buffer[1024];
    int len = SDLNet_TCP_Recv(clientSocket, buffer, sizeof(buffer));
    if (len > 0) {
        return std::string(buffer, len);
    }
    return "";
}

void Client::disconnect() {
    if (clientSocket) {
        SDLNet_TCP_Close(clientSocket);
        clientSocket = nullptr;
    }
    SDLNet_Quit();
}
