/**
 * @file        constantes.hpp
 * @brief       fichier entête qui regroupe les constantes du projet 
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 *
 *  @note
 */

#pragma once

#define SCALING_FACTOR 1.5

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320

#define DISPLAY_WIDTH SCREEN_WIDTH * SCALING_FACTOR
#define DISPLAY_HEIGHT SCREEN_HEIGHT * SCALING_FACTOR

#define TITLE_SCENE 0
#define GAME_SCENE 1

#define TEXTURE_NUMBER  13
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define MAP_WIDTH 32
#define MAP_HEIGHT 16

#define BASE_MOVE_SPEED 0.05

#define SFX_NUM 7
#define SHOOT_SFX 0
#define PAIN_SFX 1
#define DIE_SFX 2
#define ENEMY_PAIN_SFX 3
#define ENEMY_DIE_SFX 4
#define SELECT_SFX 5
#define ENTER_SFX 6


extern const char* texPaths[TEXTURE_NUMBER];
