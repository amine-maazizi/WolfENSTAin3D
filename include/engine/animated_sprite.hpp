/**
 * @file        billboard_manager.hpp
 * @brief       fichier entête de la classe qui va gérer les sprite animées
 * @author      Amine Maazizi
 * @date        2024-01-23
 * @version     1.0
 * 
 * @details
 * 
 *  
 * @note
 * 
 */


#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <iostream>

#include <engine/constantes.hpp>

class AnimatedSprite {
public:
    enum class Mode {
        PLAY_ONCE,  // Play the animation once and reset
        LOOP,       // Loop the animation continuously
        MANUAL      // Manually control the frames
    };

    AnimatedSprite(SDL_Renderer* renderer, const std::string& spriteSheetPath, int frameWidth, int frameHeight);
    ~AnimatedSprite();

    void setMode(Mode mode);
    void setFrame(int frame);
    void setLoop(bool loop);
    void setSpeed(float speed); // Frames per second

    void play();
    void stop();
    void reset(); // New method to reset animation to initial state

    void update(float deltaTime);
    void render(int x, int y);

private:
    SDL_Texture* spriteSheet;
    SDL_Renderer* renderer;

    std::vector<SDL_Rect> frames;
    int currentFrame;

    Mode mode;
    bool loop;
    float frameTime; // Time per frame
    float elapsedTime;
    bool isPlaying;

    void loadFrames(int frameWidth, int frameHeight);
};
