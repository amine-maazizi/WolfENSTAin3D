#include <engine/camera.hpp>


Camera::Camera(double x, double y, double dirX, double dirY, double mSpeed, double rSpeed)
    : position(x, y),              
      direction(dirX, dirY),         
      plane(0, 0.66),               
      moveSpeed(mSpeed),              
      rotSpeed(rSpeed) {} 


void Camera::move(int worldMap[MAP_HEIGHT][MAP_WIDTH]) {

}
