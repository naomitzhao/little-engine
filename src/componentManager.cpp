#include "componentManager.h"
#include <iostream>

const int defaultTerminalVelocity = 10;

Component::Component(SDL_Texture* texture) {
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    acceleration.x = 0;
    acceleration.y = 0;
    terminalVelocity = defaultTerminalVelocity;
    renderable = texture;
}

Component::Component() {
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    acceleration.x = 0;
    acceleration.y = 0;
    terminalVelocity = defaultTerminalVelocity;
}

void Component::updatePosition() {
    position.x += velocity.x;
    position.y += velocity.y;
}

void Component::updateVelocity(int vx, int vy) {
    velocity.x = vx;
    velocity.y = vy;
}

void Component::updateVelocity() {
    int newX = velocity.x + acceleration.x;
    int newY = velocity.y + acceleration.y;
    bool xPositive = newX > 0;
    bool yPositive = newY > 0;
    velocity.x = std::min(std::abs(newX), terminalVelocity);
    velocity.y = std::min(std::abs(newY), terminalVelocity);
    if (!xPositive) {
        velocity.x *= -1;
    }
    if (!yPositive) {
        velocity.y *= -1;
    }
}

void Component::setAcceleration(int ax, int ay) {
    acceleration.x = ax;
    acceleration.y = ay;
}

void Component::resetVelocityAcceleration() {
    velocity.x = 0;
    velocity.y = 0;
    acceleration.x = 0;
    acceleration.y = 0;
}