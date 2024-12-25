#include <engine/camera.hpp>


Camera::Camera()
    : position(12, 12),              
      direction(-1, 0),         
      plane(0, 0.66),               
      moveSpeed(0.05),              
      rotSpeed(0.03) {} 


void Camera::move(int worldMap[MAP_HEIGHT][MAP_WIDTH]) {
     const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_W]) {
        Vector2D<double> nextPosition = position + direction * moveSpeed;
        if (worldMap[int(nextPosition.getX())][int(position.getY())] == 0) {
            position.setX(nextPosition.getX());
        }
        if (worldMap[int(position.getX())][int(nextPosition.getY())] == 0) {
            position.setY(nextPosition.getY());
        }
    }

    if (keystate[SDL_SCANCODE_S]) {
        Vector2D<double> nextPosition = position - direction * moveSpeed;
        if (worldMap[int(nextPosition.getX())][int(position.getY())] == 0) {
            position.setX(nextPosition.getX());
        }
        if (worldMap[int(position.getX())][int(nextPosition.getY())] == 0) {
            position.setY(nextPosition.getY());
        }
    }

    // TODO: employer une matrice de rotation pour cela (glm ?)
    if (keystate[SDL_SCANCODE_D]) {
        double cosRot = cos(-rotSpeed);
        double sinRot = sin(-rotSpeed);

        double newDirX = direction.getX() * cosRot - direction.getY() * sinRot;
        double newDirY = direction.getX() * sinRot + direction.getY() * cosRot;
        direction.setX(newDirX);
        direction.setY(newDirY);

        double newPlaneX = plane.getX() * cosRot - plane.getY() * sinRot;
        double newPlaneY = plane.getX() * sinRot + plane.getY() * cosRot;
        plane.setX(newPlaneX);
        plane.setY(newPlaneY);
    }

    if (keystate[SDL_SCANCODE_A]) {
        double cosRot = cos(rotSpeed);
        double sinRot = sin(rotSpeed);

        double newDirX = direction.getX() * cosRot - direction.getY() * sinRot;
        double newDirY = direction.getX() * sinRot + direction.getY() * cosRot;
        direction.setX(newDirX);
        direction.setY(newDirY);

        double newPlaneX = plane.getX() * cosRot - plane.getY() * sinRot;
        double newPlaneY = plane.getX() * sinRot + plane.getY() * cosRot;
        plane.setX(newPlaneX);
        plane.setY(newPlaneY);
    }
}