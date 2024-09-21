#include "entity.h"

Entity::Entity(float w, float h): id(-1), x(0), y(0), vx(0), vy(0), ax(0), ay(0), width(w), height(h), grounded(false) {}

void Entity::updateX(float deltaTime) {
    x += vx * deltaTime;
}

void Entity::updateY(float deltaTime) {
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