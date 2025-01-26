#include <engine/gui.hpp>

// TODO: add an offset based on length of str for each GUI textual element

GUI::GUI(SDL_Renderer* rend) : renderer(rend), 
    gun(AnimatedSprite(renderer, "assets/gun_spritesheet.png", 88, 74)) {
   font = TTF_OpenFont("assets/PressStart2P-Regular.ttf", 12);
    if (font == NULL) {
        printf("SDL n'a pas pu créer le font, erreur: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    pannelSurf = IMG_Load("assets/gui_v0.png");
    if (!pannelSurf) {
        printf("SDL n'a pas pu charger la pannel du GUI: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

     // Create texture from surface
    pannelTex = SDL_CreateTextureFromSurface(renderer, pannelSurf);
    SDL_FreeSurface(pannelSurf); // Free the surface as it's no longer needed

    if (!pannelTex) {
        printf("SDL n'a pas pu creér la surface du pannel: %s\n", SDL_GetError());
        exit(1);
    }

    switch (gameMode) {
    case SOLO_MODE:
        character = new AnimatedSprite(renderer, "assets/lhuillier_spritesheet.png", 64, 64);
        break;
    case HOST_MODE:
        character = new AnimatedSprite(renderer, "assets/lhuillier_spritesheet.png", 64, 64);
        break;
    case JOIN_MODE:
        character = new AnimatedSprite(renderer, "assets/bruno_spritesheet.png", 64, 64);
        break;
    }

    character->setMode(AnimatedSprite::Mode::MANUAL);
    gun.setMode(AnimatedSprite::Mode::PLAY_ONCE);
    gun.setLoop(false); // Ensure animation plays only once
    gun.setSpeed(0.4f);

}

void GUI::render(float fps, int level, int score, int lives, int health, int ammo, bool toggleHelp) {
    // Render the background panel texture
    SDL_RenderCopy(renderer, pannelTex, NULL, NULL);

    // Helper to calculate the width based on the number of characters
    auto calculateWidth = [](const std::string& str) {
        return static_cast<int>(16 * str.length() * SCALING_FACTOR); // 16 pixels per character, scaled
    };

    // Reusable surface and texture for text
    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Rect textRect = { 0, 0, 0, static_cast<int>(32 * SCALING_FACTOR) }; // Initialize rect with common height

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
        character->setFrame(0);
    } else if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
        character->setFrame(1);
    }

    if (keystate[SDL_SCANCODE_SPACE]) {
        gun.play();
    }

    character->render(270 * SCALING_FACTOR, 253  * SCALING_FACTOR);
    gun.update(0.6f);
    gun.render(276 * SCALING_FACTOR, 176 * SCALING_FACTOR);

    if (toggleHelp) {
    // Render the FPS
    std::ostringstream fpsStream;
    fpsStream << std::fixed << std::setprecision(2) << fps << " FPS";
    std::string fpsFormatted = fpsStream.str();
    textSurface = TTF_RenderText_Solid(font, fpsFormatted.c_str(), SDL_Color{255, 255, 255});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.x = static_cast<int>(24 * SCALING_FACTOR);
    textRect.y = static_cast<int>(16 * SCALING_FACTOR);
    textRect.w = calculateWidth(fpsFormatted);  // Adjust width based on the number of characters
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    }

    // Render the level
    std::ostringstream levelStream;
    levelStream << level;
    textSurface = TTF_RenderText_Solid(font, levelStream.str().c_str(), SDL_Color{255, 255, 255});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.x = static_cast<int>(41 * SCALING_FACTOR);
    textRect.y = static_cast<int>(286 * SCALING_FACTOR);
    textRect.w = calculateWidth(levelStream.str()); // Adjust width based on the number of characters
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Render the score
    std::ostringstream scoreStream;
    scoreStream << score;
    textSurface = TTF_RenderText_Solid(font, scoreStream.str().c_str(), SDL_Color{255, 255, 255});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.x = static_cast<int>(128 * SCALING_FACTOR);
    textRect.y = static_cast<int>(286 * SCALING_FACTOR);
    textRect.w = calculateWidth(scoreStream.str()); // Adjust width based on the number of characters
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Render the lives
    std::ostringstream livesStream;
    livesStream << lives;
    textSurface = TTF_RenderText_Solid(font, livesStream.str().c_str(), SDL_Color{255, 255, 255});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.x = static_cast<int>(224 * SCALING_FACTOR);
    textRect.y = static_cast<int>(286 * SCALING_FACTOR);
    textRect.w = calculateWidth(livesStream.str()); // Adjust width based on the number of characters
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Render the health (percentage)
    std::ostringstream healthStream;
    healthStream << health << "%";
    textSurface = TTF_RenderText_Solid(font, healthStream.str().c_str(), SDL_Color{255, 255, 255});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.x = static_cast<int>(340 * SCALING_FACTOR);
    textRect.y = static_cast<int>(286 * SCALING_FACTOR);
    textRect.w = calculateWidth(healthStream.str()); // Adjust width based on the number of characters
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Render the ammo
    std::ostringstream ammoStream;
    ammoStream << ammo;
    textSurface = TTF_RenderText_Solid(font, ammoStream.str().c_str(), SDL_Color{255, 255, 255});
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect.x = static_cast<int>(427 * SCALING_FACTOR);
    textRect.y = static_cast<int>(286 * SCALING_FACTOR);
    textRect.w = calculateWidth(ammoStream.str()); // Adjust width based on the number of characters
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


GUI::~GUI() {
    delete character;
    TTF_CloseFont(font);
    SDL_FreeSurface(fpsText);
    SDL_DestroyTexture(guiTex);
    SDL_FreeSurface(pannelSurf);
    SDL_DestroyTexture(pannelTex);
}