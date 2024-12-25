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
    camera.move(worldMap);
    raycaster.cast_rays(this->camera, worldMap);
}

void Application::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 64, 96, 128, 255); 
    SDL_Rect topHalf = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &topHalf);
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); 
    SDL_Rect bottomHalf = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(renderer, &bottomHalf);

    raycaster.render(this->renderer);

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
