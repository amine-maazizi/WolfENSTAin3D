#include <engine/player.hpp>

Player::Player(Effects& fx) : fx(fx), Camera(8, 2, -1, 0, 0.05, 0.04), health(1.0f), isAlive(true), cooldown(0.0f), lives(3), score(0), ammo(100) {}

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

void Player::shoot(float dmg, BillboardManager& bbManager) {
    // Take the closest enemy who's cosine with the direction vector is in range [0, PI]
    // compute cosine of the direction vector 
    double distance = INFINITY;
    Enemy*  closest_enemy = NULL;
    double min_angle = 0.0;
    for (auto& e : bbManager.enemies) {
        double dist = (position - e.position).length(); 
        Vector2D<double> dir = (position - e.position).normalized();
        double angle = acos(direction * dir);
        if (dist < distance && angle > 3 * M_PI / 4 && dist < 4) {
            distance = (position - e.position).length();
            min_angle = angle;
            closest_enemy = &e;
        }
    }
    
    ammo--;
    if (closest_enemy) {
        fx.shakeScreen(20, 10);
        score += 100;
        closest_enemy->damage(dmg * fabs(cos(min_angle)), fx);
    }
}

void Player::process(int worldMap[MAP_HEIGHT][MAP_WIDTH], BillboardManager& bbManager) {
    // TODO: ajouter keystate comme argument de move 
    move(worldMap);
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (cooldown <= 0.0) {
        if (keystate[SDL_SCANCODE_SPACE]) {
            fx.playSfx(SHOOT_SFX);
            shoot(34, bbManager);
            cooldown = 10.0;
        } 
    } else {
        cooldown--;
    }
}