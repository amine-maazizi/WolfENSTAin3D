#include <engine/server.hpp>
#include <engine/player.hpp>

Server::Server(Uint16 port, Player* p) : currentControllerId(-1), player(p) {
    if (SDLNet_ResolveHost(&ip, NULL, port) < 0) {
        printf("SDLNet_ResolveHost failed: %s\n", SDLNet_GetError());
        exit(1);
    }
    serverSocket = SDLNet_TCP_Open(&ip);
    if (!serverSocket) {
        printf("SDLNet_TCP_Open failed: %s\n", SDLNet_GetError());
        exit(1);
    }
    printf("Server started on port %d\n", port);
}

Server::~Server() {
    for (auto client : clients) {
        SDLNet_TCP_Close(client);
    }
    SDLNet_TCP_Close(serverSocket);
    SDLNet_Quit();
}

void Server::acceptClients() {
    if (clients.size() >= 2) return; // Limit to two clients

    TCPsocket newClient = SDLNet_TCP_Accept(serverSocket);
    if (newClient) {
        clients.push_back(newClient);
        int newClientId = clients.size() - 1;

        printf("New client connected with ID: %d\n", newClientId);

        if (currentControllerId == -1) {
            currentControllerId = newClientId;
            printf("Player control assigned to client ID: %d\n", currentControllerId);
        }
    }
}

void Server::processClientActions() {
    char buffer[256];
    for (size_t i = 0; i < clients.size(); ++i) {
        TCPsocket client = clients[i];
        int len = SDLNet_TCP_Recv(client, buffer, sizeof(buffer));
        if (len <= 0) {
            if (len == 0) {
                printf("Client %zu disconnected\n", i);
            } else {
                printf("Error receiving data from client %zu: %s\n", i, SDLNet_GetError());
            }
            SDLNet_TCP_Close(client);
            clients.erase(clients.begin() + i);
            if (currentControllerId == (int)i) {
                currentControllerId = -1; // Reset control
            }
            continue;
        }

        Uint8 actionType = buffer[0];

        // Only process actions from the current controller
        if ((int)i != currentControllerId && actionType != 0x05) continue;

        switch (actionType) {
            case 0x01: // Movement
                player->position.setX(*(float*)(buffer + 1));
                player->position.setY(*(float*)(buffer + 5));
                break;

            case 0x02: // Shooting
                printf("Player is shooting\n");
                break;

            case 0x03: // Sprinting
                printf("Player is sprinting\n");
                break;

            case 0x05: // Control transfer
                currentControllerId = (currentControllerId + 1) % clients.size();
                printf("Control transferred to client ID: %d\n", currentControllerId);
                break;

            default:
                printf("Unknown action type: %d\n", actionType);
                break;
        }
    }
}

void Server::broadcastGameState() {
    char buffer[256];
    int offset = 0;

    // Serialize player state
    *(float*)(buffer + offset) = player->position.getX();
    offset += sizeof(float);
    *(float*)(buffer + offset) = player->position.getY();
    offset += sizeof(float);

    // Serialize current controller ID
    buffer[offset] = currentControllerId;
    offset += sizeof(Uint8);

    for (auto client : clients) {
        if (SDLNet_TCP_Send(client, buffer, offset) < offset) {
            printf("Failed to send game state to client: %s\n", SDLNet_GetError());
        }
    }
}

void Server::update() {
    acceptClients();
    processClientActions();
    broadcastGameState();
}
