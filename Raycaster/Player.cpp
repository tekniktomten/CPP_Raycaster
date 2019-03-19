#include "Player.hpp"

Player::Player() {
    pos = Vector2d(16, 94);
    dir = Vector2d(0, -1);
    cam = Vector2d(0.707, 0);
    movementSpeed = 5;
    actualSpeed = movementSpeed;
    forward = false;
    backward = false;
    right = false;
    left = false;
    sprint = false;
}
