#include <engine/effects.hpp>

Effects::Effects() : duration(0), magnitude(0), elapsed(0), gen(rd()), dist(0.0, 1.0) {
}

void Effects::shakeScreen(int duration, int magnitude) {
    this->duration = duration;
    this->magnitude = magnitude;
    this->elapsed = 0;
}

void Effects::applyScreenShake(SDL_Renderer *renderer, SDL_Rect *viewport) {
    if (this->elapsed < this->duration) {
        // Cast dist(gen) to int before applying the modulo operation
        int offsetX = static_cast<int>(dist(gen) * this->magnitude) % this->magnitude;
        int offsetY = static_cast<int>(dist(gen) * this->magnitude) % this->magnitude;

        this->elapsed++;

        viewport->x += offsetX;
        viewport->y += offsetY;

        SDL_RenderSetViewport(renderer, viewport);
    } else {
        SDL_RenderSetViewport(renderer, viewport);
    }
}