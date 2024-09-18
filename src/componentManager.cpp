#include "componentManager.h"
#include <iostream>

const int defaultTerminalVelocity = 10;

Component::Component(SDL_Texture* texture) {
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    terminalVelocity = defaultTerminalVelocity;
    renderable = texture;
}

Component::Component() {
    position.x = 0;
    position.y = 0;
    velocity.x = 0;
    velocity.y = 0;
    terminalVelocity = defaultTerminalVelocity;
}

void Component::updateVelocity(int dvx, int dvy) {
    int newX = velocity.x + dvx;
    int newY = velocity.y + dvy;
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

void Component::updatePosition() {
    position.x += velocity.x;
    position.y += velocity.y;
}