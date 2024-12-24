#include <raycaster.hpp>

void Raycaster::raycast(Camera& cam, int** map) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        double cameraX = 2 * x / double(MAP_WIDTH) - 1; // Coordonnée x dans l'espace camera
        Vector2D<double> rayDir(cam.direction.getX() + cam.plane.getX() * cameraX,
                                cam.direction.getY() + cam.plane.getY() * cameraX
        );

        // Les coordonnées de la carte 
        Vector2D<int> mapCoord((int)cam.position.getX(),
                            (int)cam.position.getY()
        );

        Vector2D<double> sideDist;

        Vector2D<double> deltaDist(
            (rayDir.getX() == 0) ? 1e30 : std::abs(1 / rayDir.getX()),
            (rayDir.getY() == 0) ? 1e30 : std::abs(1 / rayDir.getY())
        );

        double prepWallDist;

        Vector2D<int> step;

        int hit = 0;
        int side;

        if (rayDir.getX() < 0) {
            step.setX(-1);
            sideDist.setX((cam.position.getX() - mapCoord.getX()) * deltaDist.getX());
        } else {
            step.setX(1);
            sideDist.setX((cam.position.getX() + 1 - mapCoord.getX()) * deltaDist.getX());
        }

        if (rayDir.getY() < 0) {
            step.setY(-1);
            sideDist.setY((cam.position.getY() - mapCoord.getY()) * deltaDist.getY());
        } else {
            step.setY(-1);
            sideDist.setY((cam.position.getY() + 1 - mapCoord.getY()) * deltaDist.getY());
        }  

        // faire DDA
        while (hit == 0) {
            // sauter à l'autre celulle, soit suivant x-direction ou y-direction
            if (sideDist.getX() < sideDist.getY()) {
                sideDist.setX(sideDist.getX() + deltaDist.getX());
                mapCoord.setX(mapCoord.getX() + step.getX());
                side = 0;
            } else {
                sideDist.setY(sideDist.getY() + deltaDist.getY());
                mapCoord.setY(mapCoord.getY() + step.getY());
                side = 1;
            }
            // Vérifier si le rayon à toucher un mur
            if (map[mapCoord.getX()][mapCoord.getY()] > 0) hit = 1;
        }

        // Calculer distance projetée dans la direction de la camera
        if (side == 0) prepWallDist = (sideDist.getX() - deltaDist.getX());
        else           prepWallDist = (sideDist.getY() - deltaDist.getY());
 

        int lineHeight = (int)(MAP_HEIGHT / prepWallDist);

        int drawStart = -lineHeight / 2 + MAP_HEIGHT / 2;
        if (drawStart < 0) drawStart= 0;
        
        int drawEnd = lineHeight / 2 + MAP_HEIGHT / 2;
        if (drawEnd >= MAP_WIDTH) drawEnd = MAP_HEIGHT - 1;

        // choix de la couleur du mur
        // TO BE WRITTEN

    }
}