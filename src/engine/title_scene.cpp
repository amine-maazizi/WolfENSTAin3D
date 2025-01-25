#include <engine/title_scene.hpp>


TitleScene::TitleScene(SDL_Window* w, SDL_Renderer* r)
    : window(w), renderer(r), bgSurf(nullptr), bgTex(nullptr),
      font(nullptr), startTextSurf(nullptr), startTextTex(nullptr),
      blinkTimer(0.0f), showText(true) {
    bgMusic = Mix_LoadMUS("assets/sfx/menu.mp3");
    if (!bgMusic) {
        std::cerr << "Failed to load music! Mix Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
    loadAssets();
}

void TitleScene::loadAssets() {
    // Load background image (PNG)
    bgSurf = IMG_Load("assets/title_screen.png");
    if (!bgSurf) {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
        exit(1);
    }
    bgTex = SDL_CreateTextureFromSurface(renderer, bgSurf);
    SDL_FreeSurface(bgSurf);

    // Initialize TTF and load font
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        exit(1);
    }

    // Adjust font size dynamically
    int fontSize = static_cast<int>(20 * SCALING_FACTOR);
    font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(1);
    }

    // Create "Press Enter to Start" text surface and texture
    SDL_Color textColor = {255, 255, 255, 255};
    startTextSurf = TTF_RenderText_Blended(font, "- Press Enter to Start -", textColor);
    if (!startTextSurf) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        exit(1);
    }
    startTextTex = SDL_CreateTextureFromSurface(renderer, startTextSurf);
    SDL_FreeSurface(startTextSurf);
}


void TitleScene::cleanUp() {
    if (bgTex) SDL_DestroyTexture(bgTex);
    if (startTextTex) SDL_DestroyTexture(startTextTex);
    if (font) TTF_CloseFont(font);
    Mix_FreeMusic(bgMusic);
}

int TitleScene::process(float dt) {
    // Blink text
    blinkTimer += dt;
    if (blinkTimer >= 300.0f) {
        blinkTimer = 0.0f;
        showText = !showText;
    }
    return TITLE_SCENE;
}

void TitleScene::render(float) {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render background
    SDL_Rect bgRect = {
        0,
        0,
        static_cast<int>(SCREEN_WIDTH * SCALING_FACTOR),
        static_cast<int>(SCREEN_HEIGHT * SCALING_FACTOR)
    };
    SDL_RenderCopy(renderer, bgTex, nullptr, &bgRect);

    // Render blinking text
    if (showText) {
        int textWidth, textHeight;
        SDL_QueryTexture(startTextTex, nullptr, nullptr, &textWidth, &textHeight);
        SDL_Rect textRect = {
            static_cast<int>((SCREEN_WIDTH * SCALING_FACTOR - textWidth) / 2),
            static_cast<int>(SCREEN_HEIGHT * SCALING_FACTOR - (50 * SCALING_FACTOR)), // Adjusted for SCALING_FACTOR
            textWidth,
            textHeight
        };
        SDL_RenderCopy(renderer, startTextTex, nullptr, &textRect);
    }

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}


int TitleScene::handleInput(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_RETURN]) {
        return SELECT_SCENE; // Transition to the next scene
    }
    return TITLE_SCENE;
}

void TitleScene::onEnter() {
    Mix_PlayMusic(bgMusic, -1);
}

void TitleScene::onExit() {
    Mix_HaltMusic();
    cleanUp();
}

void TitleScene::pause() {}

void TitleScene::resume() {}
