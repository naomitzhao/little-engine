#include "componentManager.h"
#include <iostream>


Entity::Entity(SDL_Texture* texture) {
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    renderable = texture;
    grounded = true;
}

Entity::Entity() {
    x = 0;
    y = 0;
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    grounded = true;
}

void Entity::updatePosition(float deltaTime) {
    x += vx * deltaTime;
    y += vy * deltaTime;
}

void Entity::setVelocity(int newVx, int newVy) {
    vx = newVx;
    vy = newVy;
}

void Entity::setAcceleration(int newAx, int newAy) {
    ax = newAx;
    ay = newAy;
}

void Entity::applyGravity(float gravity, float deltaTime) {
    if (!grounded) {
        vy += gravity * deltaTime;
    }
}