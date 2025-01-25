#include <engine/client.hpp>

Client::Client(const char* serverIP, Uint16 port) : isController(false), playerX(0), playerY(0) {
    if (SDLNet_ResolveHost(&ip, serverIP, port) < 0) {
        printf("SDLNet_ResolveHost failed: %s\n", SDLNet_GetError());
        exit(1);
    }
    socket = SDLNet_TCP_Open(&ip);
    if (!socket) {
        printf("SDLNet_TCP_Open failed: %s\n", SDLNet_GetError());
        exit(1);
    }
    printf("Connected to server at %s:%d\n", serverIP, port);
}

Client::~Client() {
    SDLNet_TCP_Close(socket);
    SDLNet_Quit();
}

void Client::sendInput(Uint8 actionType, float x, float y) {
    if (!isController) return;

    char buffer[256];
    buffer[0] = actionType;
    *(float*)(buffer + 1) = x;
    *(float*)(buffer + 5) = y;

    SDLNet_TCP_Send(socket, buffer, 9);
}

void Client::receiveGameState() {
    char buffer[256];
    int len = SDLNet_TCP_Recv(socket, buffer, sizeof(buffer));
    if (len > 0) {
        int offset = 0;

        playerX = *(float*)(buffer + offset);
        offset += sizeof(float);
        playerY = *(float*)(buffer + offset);
        offset += sizeof(float);

        isController = (buffer[offset] == 0);
    }
}

void Client::requestControlTransfer() {
    char buffer[1];
    buffer[0] = 0x05;
    SDLNet_TCP_Send(socket, buffer, 1);
}

void Client::render() {
    printf("Rendering player at (%f, %f)\n", playerX, playerY);
    if (isController) {
        printf("You have control!\n");
    }
}
