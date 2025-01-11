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

#define TEXTURE_NUMBER  10
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define BASE_MOVE_SPEED 0.05

extern const char* texPaths[TEXTURE_NUMBER];