#include <engine/enemy.hpp>

Enemy::Enemy(Vector2D<double> pos, int id)
    : bb(std::make_unique<Billboard>(pos, id)), cooldown(0.0f), health(100), isAlive(true) {
}

Enemy::Enemy(double x, double y, int id)
    : bb(std::make_unique<Billboard>(x, y, id)), cooldown(0.0f), health(100), isAlive(true) {
}

void Enemy::damage(float dmg, Effects& fx) {
    fx.playSfx(ENEMY_PAIN_SFX);
    if (health - dmg <= 0 && isAlive) {
        fx.playSfx(ENEMY_DIE_SFX);
        isAlive = false;
        bb->visible = false;
        return;
    }
    health -= dmg;
}

void Enemy::moveEnemy(Player& p, int map[MAP_HEIGHT][MAP_WIDTH], Effects& fx, float dt_) {
    float dt = 0.06;
    if (isAlive) {
        if (cooldown <= 0.0) {
            if ((p.position - bb->position).length() < 4) {
                this->velocity = (p.position - bb->position).normalized();
                Vector2D<int> mapping = bb->position + velocity * dt;

                // Validate indices
                if (mapping.getX() < 0 || mapping.getX() >= MAP_HEIGHT || mapping.getY() < 0 || mapping.getY() >= MAP_WIDTH) {
                    std::cerr << "Error: Out of bounds mapping at position (" 
                              << mapping.getX() << ", " << mapping.getY() << ")" << std::endl;
                    return;
                }

                if ((p.position - bb->position).length() > 1) {
                    if (map[mapping.getX()][mapping.getY()] == 0) {
                        bb->position = bb->position + velocity * dt;
                    }
                } else {
                    // SHOOT
                    p.damage(0.2);
                    fx.shakeScreen(10, 10);
                    fx.reden(10, 100);
                    cooldown = 10.0;
                }
            }
        } else {
            cooldown -= 0.1;
        }
    }
}


    // AStar aStar(map);

    // std::vector<Vector2D<int>> path = aStar.findPath(start, goal);


    // if (!path.empty()) {
    //     this->position = path[1]; 
    // } else {
    //     std::cout << "No valid path found.\n";
    // }


