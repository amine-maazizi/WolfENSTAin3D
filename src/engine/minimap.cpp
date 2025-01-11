#include <engine/minimap.hpp>

void Minimap::render(SDL_Renderer* renderer, Camera& cam, int worldMap[][MAP_WIDTH]) {
    // On commence par dessiner la minimap sur le renderer
    // TODO: à avoir si on a besoin d'optimistion
    // TODO: par exemple dessiner la minimap sur une autre surface puis append le tous 
    const int tilesize = 4 * SCALING_FACTOR;
    const int psize = 3 * SCALING_FACTOR;
    const int mapsize = MAP_WIDTH * tilesize;
    // TODO: regler le décalage
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH - 1; x++)  {
            SDL_Rect dest;
            dest.x = DISPLAY_WIDTH - mapsize + (x+1) * tilesize;
            dest.y = y * tilesize;
            dest.w = tilesize;
            dest.h = tilesize;
            if (worldMap[x][y] != 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &dest);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &dest);
            }
        }
    }
    SDL_Rect dest;
    dest.x = DISPLAY_WIDTH - mapsize + (cam.position.getX()) * tilesize + psize / 2;
    dest.y = cam.position.getY() * tilesize + psize / 2;
    dest.w = psize;
    dest.h = psize;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &dest);
}   