#include <engine/effects.hpp>

Effects::Effects() : screenShake{0, 0, 0}, redening{0, 0, 0}, gen(rd()), dist(0.0, 1.0) {
}

void Effects::shakeScreen(int duration, int magnitude) {
    screenShake.duration = duration;
    screenShake.magnitude = magnitude;
    screenShake.elapsed = 0;
}

void Effects::applyScreenShake(SDL_Renderer *renderer, SDL_Rect *viewport) {
    if (screenShake.elapsed < screenShake.duration) {
        int offsetX = static_cast<int>(dist(gen) * screenShake.magnitude) % screenShake.magnitude;
        int offsetY = static_cast<int>(dist(gen) * screenShake.magnitude) % screenShake.magnitude;

        screenShake.elapsed++;

        viewport->x += offsetX;
        viewport->y += offsetY;

        SDL_RenderSetViewport(renderer, viewport);
    } else {
        SDL_RenderSetViewport(renderer, viewport);
    }
}

void Effects::reden(int duration, int magnitude) {
    redening.duration = duration;
    redening.magnitude = magnitude;
    redening.elapsed = 0;
}

void Effects::applyRedening(SDL_Renderer* renderer) {
    if (redening.elapsed < redening.duration) {
        int alpha = static_cast<int>(255 * (redening.magnitude / 10.0f));
        alpha = alpha > 255 ? 255 : alpha; // Clamp to 255
        alpha *= (1 - (float)redening.elapsed / (float)redening.duration);

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, alpha); // Red color with calculated transparency

        SDL_RenderFillRect(renderer, nullptr); // Apply red overlay to the entire screen

        redening.elapsed++;
    } else {
        // Reset blending mode once the effect is done
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
}
