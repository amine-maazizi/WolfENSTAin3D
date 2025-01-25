#include <engine/game_scene.hpp>

GameScene::GameScene(SDL_Window* w, SDL_Renderer* r) : player(Player(fx)), raycaster(Raycaster(player)), bbManager(BillboardManager(player, fx)), help(false) {
    renderer = r;
    window = w;
    bgMusic = Mix_LoadMUS("assets/sfx/game.mp3");
    if (!bgMusic) {
        printf("Failed to load music! Mix Error: %s\n", Mix_GetError());
        exit(1);
    }

       SDL_RenderClear(this->renderer);
    buffTex = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT);
    
    if (buffTex == NULL) {
        printf("SDL n'a pas pu créer la texture, erreur: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // Initialize enemies using push_back
    enemies.push_back(Enemy(3, 6, 10));
    enemies.push_back(Enemy(15, 15, 12));
    enemies.push_back(Enemy(8, 9, 12));
    enemies.push_back(Enemy(14, 16, 10));
    enemies.push_back(Enemy(13, 20, 10));
    enemies.push_back(Enemy(3, 29, 12));
    enemies.push_back(Enemy(3, 16, 10));
    enemies.push_back(Enemy(3, 23, 10));

    
    for (auto& enemy : enemies) {
        bbManager.addBillboard(enemy.bb, player); 
    }

}

GameScene::~GameScene() {
    delete gui;
    SDL_DestroyTexture(this->buffTex);
}

int GameScene::process(float dt) {
    if (gameMode == HOST_MODE && server) {
        server->update();
    }

    if (gameMode == JOIN_MODE && client) {
        // Receive game state updates from the server
        client->receiveGameState();
    }


    player.process(worldMap, this->enemies, server, client);
    for (auto& e: enemies) {
        e.moveEnemy(player, worldMap, fx, dt);
    }
    raycaster.castRays(this->player, worldMap, bbManager);
    return GAME_SCENE;
}

void GameScene::render(float fps) {
    SDL_Rect viewport = {0, 0, static_cast<int>(SCREEN_WIDTH * SCALING_FACTOR), 
                                static_cast<int>(SCREEN_HEIGHT * SCALING_FACTOR)};
    
    raycaster.render(this->renderer, this->buffTex);

    gui->render(fps, 1, player.score, player.lives, player.health * 100, player.ammo, help);  // Dummy values

    // TODO: logiquement elle doit faire partie du GUI mais elle a beacoups de dépendances donc on l'a laisse ici
    // Vue qu'elle est dèjà bien encapsulé
    if (help) {
        Minimap::render(this->renderer, this->player, enemies, worldMap);
    }


   // TODO: regrouper ses fonctions en une seule fonction de Effects
    fx.applyScreenShake(renderer, &viewport);
    fx.applyRedening(renderer);

    SDL_RenderSetViewport(renderer, &viewport);
}

int GameScene::handleInput(const Uint8* keystate) {
    if (client && !client->isController) {
            // If the client doesn't have control, ignore input
            return 0;
    }

    static bool hKeyPressed = false; 

    if (keystate[SDL_SCANCODE_H]) {
        if (!hKeyPressed) {  
            help = !help;
            hKeyPressed = true;  
        }
    } else {
        hKeyPressed = false;  
    }

    // Transfer control
    if (keystate[SDL_SCANCODE_T]) {
        if (client) client->requestControlTransfer();
    }
    
    return GAME_SCENE;
}

void GameScene::onEnter() {
    gui = new GUI(renderer);
    switch (gameMode) {
        case HOST_MODE:
            server = new Server(1234, &player); // Create a server listening on port 1234
            printf("Hosting game...\n");
            break;
        case JOIN_MODE:
            client = new Client("127.0.0.1", 1234); // Connect to a server
            printf("Joining game...\n");
            break;
    }

    Mix_PlayMusic(bgMusic, -1);
}

void GameScene::onExit() {}

void GameScene::pause() {}

void GameScene::resume() {}
