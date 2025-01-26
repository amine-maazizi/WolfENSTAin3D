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
    enemies.push_back(Enemy(8, 13, 12));
    enemies.push_back(Enemy(10, 13, 10));
    enemies.push_back(Enemy(14, 16, 10));
    enemies.push_back(Enemy(13, 20, 10));
    enemies.push_back(Enemy(3, 29, 12));
    enemies.push_back(Enemy(3, 16, 10));
    enemies.push_back(Enemy(3, 23, 10));
    enemies.push_back(Enemy(4, 23, 12));
    enemies.push_back(Enemy(8, 23, 12));

    
    for (auto& enemy : enemies) {
        bbManager.addBillboard(enemy.bb, player);  // Transfer ownership to BillboardManager
    }



}

GameScene::~GameScene() {
    delete gui;
    SDL_DestroyTexture(this->buffTex);
}

int GameScene::process(float dt) {
    player.process(worldMap, this->enemies);
    for (auto& e: enemies) {
        e.moveEnemy(player, worldMap, fx, dt);
    }
    raycaster.castRays(this->player, worldMap, bbManager);
    if (!player.isAlive) {
        return TITLE_SCENE;
    }
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
    static bool hKeyPressed = false; 

    if (keystate[SDL_SCANCODE_H]) {
        if (!hKeyPressed) {  
            help = !help;
            hKeyPressed = true;  
        }
    } else {
        hKeyPressed = false;  
    }
    
    return GAME_SCENE;
}

void GameScene::onEnter() {
    gui = new GUI(renderer);
    Mix_PlayMusic(bgMusic, -1);
}

void GameScene::onExit() {}

void GameScene::pause() {}

void GameScene::resume() {}
