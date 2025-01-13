#include <engine/enemy.hpp>

Enemy::Enemy(Vector2D<double> pos, int id) :  Billboard(pos, id) {}

Enemy::Enemy(double x, double y, int id) : Billboard(x, y, id) {}

void Enemy::moveEnemy(Camera& cam, int map[MAP_HEIGHT][MAP_WIDTH]) {
    float dt = 0.06; // pour le moment
    if ((cam.position - position).length() > 1) {
    this->velocity = (cam.position - position).normalized();
    this->position = position + velocity * dt; 
    }

    // AStar aStar(map);

    // std::vector<Vector2D<int>> path = aStar.findPath(start, goal);


    // if (!path.empty()) {
    //     this->position = path[1]; 
    // } else {
    //     std::cout << "No valid path found.\n";
    // }
}

