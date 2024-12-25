#include <engine/raycaster.hpp>
#include <SDL2/SDL.h>
#include <cmath>

void Raycaster::raycast(Camera& cam, int map[][24], SDL_Renderer* renderer) {
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;

    // Loop through each vertical stripe of the screen
    for (int x = 0; x < screenWidth; x++) {
        // Calculate ray direction for the current column
        double cameraX = 2.0 * x / screenWidth - 1.0; // Camera plane coordinates
        double rayDirX = cam.direction.getX() + cam.plane.getX() * cameraX;
        double rayDirY = cam.direction.getY() + cam.plane.getY() * cameraX;

        // Map square the ray is in
        int mapX = int(cam.position.getX());
        int mapY = int(cam.position.getY());

        // Length of ray to the next x or y side
        double sideDistX, sideDistY;

        // Length of ray from one x or y-side to the next
        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
        double perpWallDist;

        // Direction to step in x or y (+1 or -1)
        int stepX, stepY;

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (cam.position.getX() - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - cam.position.getX()) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (cam.position.getY() - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - cam.position.getY()) * deltaDistY;
        }

        // Perform DDA
        int hit = 0; // Wall hit flag
        int side;    // Was the wall hit vertical or horizontal?
        while (hit == 0) {
            // Jump to the next map square
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // Hit x-side
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // Hit y-side
            }

            // Check if ray hit a wall
            if (map[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance to the wall
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else perpWallDist = (sideDistY - deltaDistY);

        // Calculate height of the wall
        int lineHeight = (int)(screenHeight / perpWallDist);

        // Calculate the lowest and highest pixel to fill in the stripe
        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        // Choose wall color
        SDL_Color color;
        switch (map[mapX][mapY]) {
            case 1: color = {255, 0, 0, 255}; break; // Red
            case 2: color = {0, 255, 0, 255}; break; // Green
            case 3: color = {0, 0, 255, 255}; break; // Blue
            case 4: color = {255, 255, 0, 255}; break; // Yellow
            default: color = {255, 255, 255, 255}; break; // White
        }

        // Darken color for y-sides
        if (side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        // Render the wall stripe
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }

    // Player Movement
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_UP]) {
        if (map[int(cam.position.getX() + cam.direction.getX() * cam.moveSpeed)][int(cam.position.getY())] == 0)
            cam.position.setX(cam.position.getX() + cam.direction.getX() * cam.moveSpeed);
        if (map[int(cam.position.getX())][int(cam.position.getY() + cam.direction.getY() * cam.moveSpeed)] == 0)
            cam.position.setY(cam.position.getY() + cam.direction.getY() * cam.moveSpeed);
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        if (map[int(cam.position.getX() - cam.direction.getX() * cam.moveSpeed)][int(cam.position.getY())] == 0)
            cam.position.setX(cam.position.getX() - cam.direction.getX() * cam.moveSpeed);
        if (map[int(cam.position.getX())][int(cam.position.getY() - cam.direction.getY() * cam.moveSpeed)] == 0)
            cam.position.setY(cam.position.getY() - cam.direction.getY() * cam.moveSpeed);
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
        double oldDirX = cam.direction.getX();
        cam.direction.setX(cam.direction.getX() * cos(cam.rotSpeed) - cam.direction.getY() * sin(cam.rotSpeed));
        cam.direction.setY(oldDirX * sin(cam.rotSpeed) + cam.direction.getY() * cos(cam.rotSpeed));
        double oldPlaneX = cam.plane.getX();
        cam.plane.setX(cam.plane.getX() * cos(cam.rotSpeed) - cam.plane.getY() * sin(cam.rotSpeed));
        cam.plane.setY(oldPlaneX * sin(cam.rotSpeed) + cam.plane.getY() * cos(cam.rotSpeed));
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        double oldDirX = cam.direction.getX();
        cam.direction.setX(cam.direction.getX() * cos(-cam.rotSpeed) - cam.direction.getY() * sin(-cam.rotSpeed));
        cam.direction.setY(oldDirX * sin(-cam.rotSpeed) + cam.direction.getY() * cos(-cam.rotSpeed));
        double oldPlaneX = cam.plane.getX();
        cam.plane.setX(cam.plane.getX() * cos(-cam.rotSpeed) - cam.plane.getY() * sin(-cam.rotSpeed));
        cam.plane.setY(oldPlaneX * sin(-cam.rotSpeed) + cam.plane.getY() * cos(-cam.rotSpeed));
    }
}
