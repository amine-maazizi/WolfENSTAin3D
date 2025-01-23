#include <engine/application.hpp>

Application::Application() {
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

     if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! Mix Error: %s\n", Mix_GetError());
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

    scenes[0] = new GameScene();
}

Application::~Application() {
    delete scenes[0];
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    Mix_CloseAudio();
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

}

void Application::render(float fps) {


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    

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
