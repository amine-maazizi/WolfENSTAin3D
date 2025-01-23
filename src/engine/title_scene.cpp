#include <engine/title_scene.hpp>

TitleScene::TitleScene(SDL_Window* w, SDL_Renderer* r) {
    window = w;
    renderer = r;
    bgMusic = Mix_LoadMUS("assets/sfx/menu.mp3");
    if (!bgMusic) {
        printf("Failed to load music! Mix Error: %s\n", Mix_GetError());
        exit(1);
    } 
}
    
int TitleScene::process(float dt) {
    return TITLE_SCENE;
}

void TitleScene::render(float) {}             
int TitleScene::handleInput(const Uint8* keystate) {
    if (keystate[SDL_SCANCODE_RETURN]) 
        return GAME_SCENE;
    return TITLE_SCENE;
}     



void TitleScene::onEnter() {
    Mix_PlayMusic(bgMusic, -1);
}

void TitleScene::onExit() {}

void TitleScene::pause() {}

void TitleScene::resume() {}
