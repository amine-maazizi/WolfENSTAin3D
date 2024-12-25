#include <engine/application.hpp>

Application::Application() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'a pas pu être intialiser, erreur : %s\n", SDL_GetError());
        exit(1);
    }

    this->window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
}

Application::~Application() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();

}


void Application::handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            default:
                break;
            
        }
    }
}


void Application::process() {
}

void Application::render() {
    SDL_SetRenderDrawColor(this->renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);
    Raycaster::raycast(this->camera, worldMap, this->renderer);
    SDL_RenderPresent(this->renderer);
}

void Application::run() {
    while (1) {
        handleInput();
        process();
        render();

        SDL_Delay(16);
    }
}
