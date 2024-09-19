#include "entity.h"

Entity::Entity(int w, int h): width(w), height(h), grounded(false) {}

void Entity::updatePosition(float deltaTime) {
    x += vx * deltaTime;
    y += vy * deltaTime;
}

void Entity::setVelocity(float newVx, float newVy) {
    vx = newVx;
    vy = newVy;
}

void Entity::setAcceleration(float newAx, float newAy) {
    ax = newAx;
    ay = newAy;
}

void Entity::applyGravity(float gravity, float deltaTime) {
    if (!grounded) {
        vy += gravity * deltaTime;
    }
}

void Entity::jump(float jumpStrength) {
    if (grounded) {
        vy = -jumpStrength;
        grounded = false;
    }
}