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

    this->window = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
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

    font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 24);
    if (font == NULL) {
        printf("SDL n'a pas pu créer le font, erreur: %s\n", SDL_GetError());
        SDL_DestroyTexture(buffTex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

Application::~Application() {
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
    camera.move(worldMap);
    raycaster.cast_rays(this->camera, worldMap);
}

void Application::render(float fps) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    raycaster.render(this->renderer, this->buffTex);

    // creation d'une string litteral comportant le fps avec 2 digit precision
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << fps << " FPS";
    std::string formatted = oss.str();

    SDL_Surface* fpsText = TTF_RenderText_Solid(font, 
                    formatted.c_str(), 
                    SDL_Color {255, 255, 255});

    // TODO: créer une classe appart pour le GUI
    SDL_Texture* gui = SDL_CreateTextureFromSurface(renderer, fpsText);
    SDL_Rect gui_rect;
    gui_rect.x = 0;  
    gui_rect.y = 0; 
    gui_rect.w = 256; 
    gui_rect.h = 64; 

    SDL_RenderCopy(renderer, gui, NULL, &gui_rect);

    // TODO: pas optimale
    SDL_FreeSurface(fpsText);
    SDL_DestroyTexture(gui);

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
