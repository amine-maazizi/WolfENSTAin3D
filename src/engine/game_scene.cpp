#include <engine/game_scene.hpp>

GameScene::GameScene(SDL_Window* w, SDL_Renderer* r) : player(Player(fx)), raycaster(Raycaster(player)), bbManager(BillboardManager(player, fx)) {
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

    gui = new GUI(renderer);

}

GameScene::~GameScene() {
    free(gui);
    SDL_DestroyTexture(this->buffTex);
}

int GameScene::process(float dt) {
    player.process(worldMap, this->bbManager);
    bbManager.processEnemies(this->player, worldMap);
    raycaster.castRays(this->player, worldMap, bbManager);
    return GAME_SCENE;
}

void GameScene::render(float fps) {
    SDL_Rect viewport = {0, 0, static_cast<int>(SCREEN_WIDTH * SCALING_FACTOR), 
                                static_cast<int>(SCREEN_HEIGHT * SCALING_FACTOR)};
    
    raycaster.render(this->renderer, this->buffTex);

    gui->render(fps, 1, player.score, player.lives, player.health * 100, player.ammo);  // Dummy values

    // TODO: logiquement elle doit faire partie du GUI mais elle a beacoups de dépendances donc on l'a laisse ici
    // Vue qu'elle est dèjà bien encapsulé
    Minimap::render(this->renderer, this->player, this->bbManager.enemies, worldMap);


   // TODO: regrouper ses fonctions en une seule fonction de Effects
    fx.applyScreenShake(renderer, &viewport);
    fx.applyRedening(renderer);

    SDL_RenderSetViewport(renderer, &viewport);
}

int GameScene::handleInput(const Uint8* keystate) {
    return GAME_SCENE;
}

void GameScene::onEnter() {
    Mix_PlayMusic(bgMusic, -1);
}

void GameScene::onExit() {}

void GameScene::pause() {}

void GameScene::resume() {}
