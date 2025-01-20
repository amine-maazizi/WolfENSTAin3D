#include <engine/player.hpp>

Player::Player() : Camera(), life(1.0f), isAlive(true) {}

void Player::damage(float dmg) {
    if (life - dmg <= 0) {
        isAlive = false;
        return;
    }
    life -= dmg;
}