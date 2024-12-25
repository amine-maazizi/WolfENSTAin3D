#include <engine/raycaster.hpp>
#include <SDL2/SDL.h>
#include <cmath>

Raycaster::Raycaster() {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        this->dataMap[x] = std::make_tuple(SDL_Color {0, 0, 0}, -1);
    }
}

void Raycaster::cast_rays(Camera& cam, int worldMap[][MAP_WIDTH]) {
    // Parcourir toute bande verticale de l'écran
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calcul de la direction du rayon en x
        double cameraX = 2.0 * x / SCREEN_WIDTH - 1.0; // [-1, 1]
        Vector2D<double> rayDir(
            cam.direction.getX() + cam.plane.getX() * cameraX,
            cam.direction.getY() + cam.plane.getY() * cameraX
        );

        ////////// DDA ALGORITHM //////////
        // la cellule ou se trouve le rayon à l'instant
        Vector2D<int> map(
            cam.position.getX(),
            cam.position.getY()
        );

        // longueur du rayon suivant les direction x et y
        Vector2D<double> sideDist;

        // longeur du rayon de la position x (resp. y) vers la pochaine
        Vector2D<double> deltaDist(
            (rayDir.getX() == 0) ? 1e30 : std::abs(1 / rayDir.getX()),
            (rayDir.getY() == 0) ? 1e30 : std::abs(1 / rayDir.getY())
        );

        // Va être utilisé pour calculer la longeur du rayon
        double perpWallDist;

        // Direction du pas suivant x ou y (+1 or -1)
        Vector2D<int> step;

        // Calculat des valeurs intiale
        if (rayDir.getX() < 0) {
            step.setX(-1);
            sideDist.setX((cam.position.getX() - map.getX()) * deltaDist.getX());
        } else {
            step.setX(1);
            sideDist.setX((map.getX() + 1.0 - cam.position.getX()) * deltaDist.getX());
        }
        if (rayDir.getY() < 0) {
            step.setY(-1);
            sideDist.setY((cam.position.getY() - map.getY()) * deltaDist.getY());
        } else {
            step.setY(1);
            sideDist.setY((map.getY() + 1.0 - cam.position.getY()) * deltaDist.getY());
        }

        // application du  DDA
        int hit = 0; 
        bool wasHorizontal; // nature de la collision
        while (hit == 0) {
            // saut vers la prochaine cellule
            if (sideDist.getX() < sideDist.getY()) {
                sideDist.setX(sideDist.getX() + deltaDist.getX());
                map.setX(map.getX() + step.getX());
                wasHorizontal = true; // collision horizontale
            } else {
                sideDist.setY(sideDist.getY() + deltaDist.getY());
                map.setY(map.getY() + step.getY());
                wasHorizontal = false; // collision verticale
            }

            // On verifie si on a atteint un mur
            if (worldMap[map.getX()][map.getY()] > 0) hit = 1;
        }

        // Calcul de la distance au murs
        if (wasHorizontal) perpWallDist = (sideDist.getX() - deltaDist.getX());
        else perpWallDist = (sideDist.getY() - deltaDist.getY());

        // choix de la couleur
        SDL_Color color;
        switch (worldMap[map.getX()][map.getY()]) {
            case 1: color = {255, 0, 0, 255}; break; // Red
            case 2: color = {0, 255, 0, 255}; break; // Green
            case 3: color = {0, 0, 255, 255}; break; // Blue
            case 4: color = {255, 255, 0, 255}; break; // Yellow
            default: color = {255, 255, 255, 255}; break; // White
        }

        // Ajouter de l'ombre si la collision était verticale
        if (!wasHorizontal) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        this->dataMap[x] = std::make_tuple(color, perpWallDist);
    }
}


void Raycaster::render(SDL_Renderer* renderer) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        if (dataMap.find(x) != dataMap.end()) {
            Color color;
            Distance distance;
            std::tie(color, distance) = dataMap[x];

            // Calcul de la longeur de sa représentation
            int lineHeight = (int)(SCREEN_HEIGHT / distance);

            // Repartition de cette longeur de manière centrée
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        
            // Render the wall stripe
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
        }
    }
}   