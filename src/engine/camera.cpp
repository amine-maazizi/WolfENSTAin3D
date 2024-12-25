#include <engine/camera.hpp>


// Constructor Implementation
Camera::Camera() {
    // Default position in open space
    position = Vector2D<double>(12.5, 12.5);

    // Default direction (facing negative X-axis)
    direction = Vector2D<double>(-1.0, 0.0);

    // Camera plane (orthogonal to direction vector for FOV)
    plane = Vector2D<double>(0.0, 0.66);

    // Default movement and rotation speeds
    moveSpeed = 0.05;
    rotSpeed = 0.03;
}
