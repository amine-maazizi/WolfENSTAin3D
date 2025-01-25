#include <engine/player.hpp>

Player::Player(Effects& fx) : fx(fx), Camera(8, 2, -1, 0, 0.05, 0.04), health(1.0f), isAlive(true), cooldown(0.0f), lives(3), score(0), ammo(100) {
    switch (gameMode) {
        case SOLO_MODE:
            id = 1;
            break;
        case HOST_MODE:
            id = 1;
            break;
        case JOIN_MODE:
            id = 2;
            break;
    }
}

void Player::damage(float dmg) {
    health -= dmg;
    fx.playSfx(PAIN_SFX);
    if (health - dmg <= 0) {
        if (lives > 0) {
            fx.playSfx(DIE_SFX);
            lives--;
            health = 1.0f;
        }
        return;
    }
}

void Player::shoot(float dmg, std::vector<Enemy>& enemies) {
    // Take the closest enemy who's cosine with the direction vector is in range [0, PI]
    // compute cosine of the direction vector 
    double distance = INFINITY;
    Enemy*  closest_enemy = NULL;
    double min_angle = 0.0;
    for (auto& e : enemies) {
        if (e.isAlive) {
            double dist = (position - e.bb->position).length(); 
            Vector2D<double> dir = (position - e.bb->position).normalized();
            double angle = acos(direction * dir);
            if (dist < distance && angle > 3 * M_PI / 4 && dist < 4) {
                distance = (position - e.bb->position).length();
                min_angle = angle;
                closest_enemy = &e;
            }
        }
    }
    
    ammo--;
    if (closest_enemy) {
        fx.shakeScreen(20, 10);
        score += 100;
        closest_enemy->damage(dmg * fabs(cos(min_angle)), fx);
    }
}

void Player::process(int worldMap[MAP_HEIGHT][MAP_WIDTH], std::vector<Enemy>& enemies) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    // Movement (W or UP arrow)
    if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) {
        Vector2D<double> nextPosition = position + direction * moveSpeed;
        if (worldMap[int(nextPosition.getX())][int(position.getY())] == 0) {
            position.setX(nextPosition.getX());
        }
        if (worldMap[int(position.getX())][int(nextPosition.getY())] == 0) {
            position.setY(nextPosition.getY());
        }
    }

    // Backward movement (S or DOWN arrow)
    if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) {
        Vector2D<double> nextPosition = position - direction * moveSpeed;
        if (worldMap[int(nextPosition.getX())][int(position.getY())] == 0) {
            position.setX(nextPosition.getX());
        }
        if (worldMap[int(position.getX())][int(nextPosition.getY())] == 0) {
            position.setY(nextPosition.getY());
        }
    }

    // Rotation (D/RIGHT or A/LEFT)
    if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
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

    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
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

    // Sprinting (SHIFT)
    if (keystate[SDL_SCANCODE_LSHIFT]) {
        moveSpeed = BASE_MOVE_SPEED * 2.0; // Double speed for sprinting
    } else {
        moveSpeed = BASE_MOVE_SPEED;
    }

    // Shooting (SPACE)
    if (cooldown <= 0.0) {
        if (keystate[SDL_SCANCODE_SPACE]) {
            fx.playSfx(SHOOT_SFX);
            shoot(34, enemies);
            cooldown = 10.0;
        }
    } else {
        cooldown--;
    }


}
