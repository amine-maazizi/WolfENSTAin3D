#include <engine/application.hpp>

Application::Application() : raycaster(Raycaster(player)), bbManager(BillboardManager(player)) {
    // TODO: ajouter SQL_Quit() a toute les init
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'a pas pu être intialiser, erreur : %s\n", SDL_GetError());
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL Image n'a pas pu être intialiser, erreur : %s\n", IMG_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("SDL TTF n'a pas pu être intialiser, erreur : %s\n", TTF_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow("Raycasting", 
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            SCALING_FACTOR * SCREEN_WIDTH, SCALING_FACTOR * SCREEN_HEIGHT, 
                            SDL_WINDOW_SHOWN);
    if (this->window == NULL) {
        printf("SDL n'a pas pu créer la fenêtre, erreur : %s\n", SDL_GetError());
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    if (this->renderer == NULL) {
        printf("SDL n'a pas pu créer le renderer, erreur : %s\n", SDL_GetError());
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

Application::~Application() {
    free(gui);
    SDL_DestroyTexture(this->buffTex);
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    IMG_Quit();
    SDL_Quit();

}


void Application::handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    exit(0);
                break;
            default:
                break;
            
        }
    }
}


void Application::process() {
    player.move(worldMap);
    bbManager.processEnemies(this->player, worldMap, fx);
    raycaster.cast_rays(this->player, worldMap, bbManager);
}

void Application::render(float fps) {
    SDL_Rect viewport = {0, 0, static_cast<int>(SCREEN_WIDTH * SCALING_FACTOR), 
                                static_cast<int>(SCREEN_HEIGHT * SCALING_FACTOR)};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    raycaster.render(this->renderer, this->buffTex);

    gui->render(fps, 1, 0, 3, player.life * 100, 100);  // Dummy values

    // TODO: logiquement elle doit faire partie du GUI mais elle a beacoups de dépendances donc on l'a laisse ici
    // Vue qu'elle est dèjà bien encapsulé
    Minimap::render(this->renderer, this->player, this->bbManager.enemies, worldMap);


   // TODO: regrouper ses fonctions en une seule fonction de Effects
    fx.applyScreenShake(renderer, &viewport);
    fx.applyRedening(renderer);
    
    SDL_RenderSetViewport(renderer, &viewport);

    SDL_RenderPresent(this->renderer);
}

void Application::run() {
    Uint32 dt, lastTime;
    float fps = 0.0f;
    while (1) {
        lastTime = SDL_GetTicks();

        handleInput();
        process();
        render(fps);

        SDL_Delay(16);
        dt = SDL_GetTicks() - lastTime;
        fps = (dt > 0) ? 1000.0f / dt : 0.0f;
    }
}
