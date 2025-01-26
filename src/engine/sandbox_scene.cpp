#include <engine/sandbox_scene.hpp>

SandboxScene::SandboxScene(SDL_Window* window, SDL_Renderer* renderer)
    : window(window), renderer(renderer), player(Player(fx)), raycaster(Raycaster(player)),
    bbManager(BillboardManager(player, fx)) {
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
    }

// Core functions
int SandboxScene::process(float dt) {
    player.process(worldMap, this->enemies);
    raycaster.castRays(this->player, worldMap, bbManager);
    return SANDBOX_SCENE; // Placeholder return
}


void SandboxScene::render(float dt) {
    // Call the raycaster to render onto the renderer and buffer texture
    raycaster.render(this->renderer, this->buffTex);

    // Rendering logic here
    SDL_RenderPresent(this->renderer); // Present the rendered content on the screen

    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_M])
        saveCurrentFrameAsPNG("output.png");
}

void SandboxScene::saveCurrentFrameAsPNG(const std::string& filename) {
    // Get the dimensions of the renderer
    int width, height;
    SDL_GetRendererOutputSize(this->renderer, &width, &height);

    // Allocate a pixel buffer
    void* pixels = malloc(width * height * 4); // 4 bytes per pixel (RGBA)
    if (!pixels) {
        SDL_Log("Failed to allocate pixel buffer");
        return;
    }

    // Read pixels from the renderer into the buffer
    if (SDL_RenderReadPixels(
            this->renderer,
            nullptr,                   // Read the entire renderer
            SDL_PIXELFORMAT_RGBA32,    // Format to read the pixels in
            pixels,                    // Buffer to store the pixels
            width * 4                  // Pitch (bytes per row)
        ) != 0) {
        SDL_Log("Failed to read pixels: %s", SDL_GetError());
        free(pixels);
        return;
    }

    // Create an SDL_Surface from the pixel buffer
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        pixels, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        free(pixels);
        return;
    }

    // Save the surface as a PNG
    if (IMG_SavePNG(surface, filename.c_str()) != 0) {
        SDL_Log("Failed to save PNG: %s", IMG_GetError());
    } else {
        SDL_Log("Successfully saved renderer output to %s", filename.c_str());
    }

    // Cleanup
    SDL_FreeSurface(surface);
    free(pixels);
}


int SandboxScene::handleInput(const Uint8* keystate) {
    return SANDBOX_SCENE; // Placeholder return
}

// Lifecycle management
void SandboxScene::onEnter() {
    Mix_PlayMusic(bgMusic, -1);
}

void SandboxScene::onExit() {
    // Cleanup logic here
}

void SandboxScene::pause() {
    // Pause logic here
}

void SandboxScene::resume() {
    // Resume logic here
}

// Helper functions
void SandboxScene::loadAssets() {
    // Asset loading logic here
}

void SandboxScene::cleanUp() {
    SDL_DestroyTexture(this->buffTex);
}
