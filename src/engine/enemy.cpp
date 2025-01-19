#include <engine/enemy.hpp>

Enemy::Enemy(Vector2D<double> pos, int id) :  Billboard(pos, id), cooldown(0.0f) {
}

Enemy::Enemy(double x, double y, int id) : Billboard(x, y, id), cooldown(0.0f) {}

void Enemy::moveEnemy(Camera& cam, int map[MAP_HEIGHT][MAP_WIDTH], Effects& fx) {
    float dt = 0.06; // pour le moment
    
    if (cooldown <= 0.0) {
        if ((cam.position - position).length() < 4) {
            this->velocity = (cam.position - position).normalized();
            Vector2D<int> mapping = position + velocity * dt;
            if ((cam.position - position).length() > 1 ) {
                if (map[mapping.getX()][mapping.getY()] == 0) 
                    this->position = position + velocity * dt; 
            } else {
                // SHOOT
                fx.shakeScreen(10, 10);
                cooldown = 10.0; // valeur modifiable par la suite pas un litteral
            }
        }
    } else {
        cooldown -= 0.1;
    }

    // AStar aStar(map);

    // std::vector<Vector2D<int>> path = aStar.findPath(start, goal);


    // if (!path.empty()) {
    //     this->position = path[1]; 
    // } else {
    //     std::cout << "No valid path found.\n";
    // }
}

