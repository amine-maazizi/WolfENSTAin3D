#include <engine/select_scene.hpp>
#include <engine/constantes.hpp>

SelectScene::SelectScene(SDL_Window* w, SDL_Renderer* r)
    : window(w), renderer(r), bgMusic(nullptr),
      font(nullptr), menuOptions({"Solo Mode", "Host Game", "Join Game"}), 
      selectedOption(-1), blinkTimer(0.0f), showText(true), isKeyPressed(false) {
    loadAssets();
}

void SelectScene::loadAssets() {
    // Initialize TTF
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        exit(1);
    }

    // Load font
    font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", static_cast<int>(16 * SCALING_FACTOR));
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        exit(1);
    }

    // Load background music
    bgMusic = Mix_LoadMUS("assets/sfx/select_menu.mp3");
    if (!bgMusic) {
        std::cerr << "Failed to load music! Mix Error: " << Mix_GetError() << std::endl;
        exit(1);
    }
}

void SelectScene::cleanUp() {
    if (font) TTF_CloseFont(font);
    if (bgMusic) Mix_FreeMusic(bgMusic);
}

int SelectScene::process(float dt) {
    // Blink effect for the hovered option
    blinkTimer += dt;
    if (blinkTimer >= 0.5f) {
        blinkTimer = 0.0f;
        showText = !showText;
    }
    return SELECT_SCENE;
}

void SelectScene::render(float) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Render logo background color
    SDL_SetRenderDrawColor(renderer, 0, 80, 240, 255); // ENSTA logo blue
    SDL_Rect bgRect = {0, 0, static_cast<int>(SCREEN_WIDTH * SCALING_FACTOR), static_cast<int>(SCREEN_HEIGHT * SCALING_FACTOR)};
    SDL_RenderFillRect(renderer, &bgRect);

    // Render menu options
    SDL_Color normalColor = {255, 255, 255, 255}; // White
    SDL_Color hoverColor = {255, 155, 0, 255};   // Yellow for hovered option

    int startY = static_cast<int>((SCREEN_HEIGHT / 3) * SCALING_FACTOR);
    for (size_t i = 0; i < menuOptions.size(); ++i) {
        SDL_Color color = (i == selectedOption && showText) ? hoverColor : normalColor;

        SDL_Surface* textSurf = TTF_RenderText_Blended(font, menuOptions[i].c_str(), color);
        SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurf);

        int textWidth = textSurf->w;
        int textHeight = textSurf->h;
        SDL_Rect textRect = {
            static_cast<int>((SCREEN_WIDTH * SCALING_FACTOR - textWidth) / 2),
            startY + static_cast<int>(i * 50 * SCALING_FACTOR),
            textWidth,
            textHeight
        };

        SDL_RenderCopy(renderer, textTex, nullptr, &textRect);

        // Free resources for this iteration
        SDL_FreeSurface(textSurf);
        SDL_DestroyTexture(textTex);
    }

    // Present the rendered frame
    SDL_RenderPresent(renderer);
}

int SelectScene::handleInput(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_DOWN]) {
        if (!isKeyPressed) {
            isKeyPressed = true;
            selectedOption = (selectedOption + 1) % static_cast<int>(menuOptions.size());
        }
    } else if (keystate[SDL_SCANCODE_UP]) {
        if (!isKeyPressed) {
            isKeyPressed = true;
            selectedOption = (selectedOption - 1 + static_cast<int>(menuOptions.size())) % static_cast<int>(menuOptions.size());
        }
    } else if (keystate[SDL_SCANCODE_RETURN]) {
        if (selectedOption >= 0) {
            gameMode = selectedOption;
            return GAME_SCENE; // Transition to the selected scene
        }
    } else {
        isKeyPressed = false; // Reset key press flag when no key is pressed
    }

    return SELECT_SCENE;
}

void SelectScene::onEnter() {
    Mix_PlayMusic(bgMusic, -1);
}

void SelectScene::onExit() {
    Mix_HaltMusic();
    cleanUp();
}

void SelectScene::pause() {}

void SelectScene::resume() {}
