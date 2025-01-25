// AnimatedSprite.cpp
#include <engine/animated_sprite.hpp>

AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight)
    : renderer(renderer), spriteSheet(nullptr), currentFrame(0), mode(Mode::MANUAL), loop(false), frameTime(0.1f), elapsedTime(0.0f), isPlaying(false) {
    spriteSheet = IMG_LoadTexture(renderer, spriteSheetPath.c_str());
    if (!spriteSheet) {
        std::cerr << "Failed to load sprite sheet: " << IMG_GetError() << std::endl;
        return;
    }
    loadFrames(frameWidth, frameHeight); // Do not scale frame sizes here
}

AnimatedSprite::~AnimatedSprite() {
    if (spriteSheet) {
        SDL_DestroyTexture(spriteSheet);
    }
}

void AnimatedSprite::setMode(Mode mode) {
    this->mode = mode;
}

void AnimatedSprite::setFrame(int frame) {
    if (frame >= 0 && frame < static_cast<int>(frames.size())) {
        currentFrame = frame;
    }
}

void AnimatedSprite::setLoop(bool loop) {
    this->loop = loop;
}

void AnimatedSprite::setSpeed(float speed) {
    if (speed > 0.0f) {
        frameTime = 1.0f / speed;
    }
}

void AnimatedSprite::play() {
    if (!isPlaying) {
        isPlaying = true;
        elapsedTime = 0.0f;
        currentFrame = 0; // Restart animation
    }
}

void AnimatedSprite::stop() {
    isPlaying = false;
}

void AnimatedSprite::reset() {
    isPlaying = false;
    currentFrame = 0; // Reset to the first frame
}

void AnimatedSprite::update(float deltaTime) {
    if (!isPlaying || mode == Mode::MANUAL) {
        return;
    }

    elapsedTime += deltaTime;

    if (elapsedTime >= frameTime) {
        elapsedTime -= frameTime;
        currentFrame++;

        if (currentFrame >= static_cast<int>(frames.size())) {
            if (mode == Mode::LOOP) {
                currentFrame = 0; // Restart loop
            } else if (mode == Mode::PLAY_ONCE) {
                currentFrame = 0; // Reset to initial frame after play once
                isPlaying = false; // Stop animation
            }
        }
    }
}

void AnimatedSprite::render(int x, int y) {
    if (!spriteSheet || frames.empty()) {
        return;
    }

    // Apply scaling to the destination rectangle
    SDL_Rect destRect = {x, y, frames[currentFrame].w * SCALING_FACTOR, frames[currentFrame].h * SCALING_FACTOR};

    SDL_RenderCopy(renderer, spriteSheet, &frames[currentFrame], &destRect);
}

void AnimatedSprite::loadFrames(int frameWidth, int frameHeight) {
    if (!spriteSheet) {
        return;
    }

    int textureWidth, textureHeight;
    SDL_QueryTexture(spriteSheet, nullptr, nullptr, &textureWidth, &textureHeight);

    // Generate frame rectangles without scaling
    for (int y = 0; y < textureHeight; y += frameHeight) {
        for (int x = 0; x < textureWidth; x += frameWidth) {
            SDL_Rect frame = {x, y, frameWidth, frameHeight};
            frames.push_back(frame);
        }
    }
}
