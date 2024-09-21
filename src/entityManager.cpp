#include "entityManager.h"
#include <iostream>

Entity* EntityManager::createEntity(float width, float height) {
    Entity* newEntity = new Entity(width, height);
    newEntity->id = entities.size();
    entities.push_back(newEntity);
    return newEntity;
}


bool EntityManager::isGroundCollision(Entity& a, Entity& b) {
    if (a.y + a.height >= b.y && (a.x < b.x + b.width && a.x + a.width > b.x) && a.y + a.height <= b.y + b.height && a.y < b.y) {
        return true;
    }
    return false;
}

void EntityManager::setGrounded(Entity& a) {
    for (int i = 0; i < entities.size(); i++) {
        if (entities[i]->id != a.id && isGroundCollision(a, *entities[i])) {
            a.grounded = true;
            return;
        }
    }
    a.grounded = false;
}

void EntityManager::resolveVerticalCollision(Entity& a, Entity& b) {
    if (!(a.y + a.height > b.y && a.y < b.y + b.height) || !(a.x + a.width > b.x && a.x < b.x + b.width)) {
        return;
    }
    if (a.vy > 0) {
        a.y = b.y - a.height;
        a.vy = 0;
        a.grounded = true;
    } else if (a.vy < 0) {
        a.y = b.y + b.height;
        a.vy = 0;
    }
}

void EntityManager::resolveVerticalCollisions(Entity& a) {
    for (int i = 0; i < entities.size(); i++) { 
        if (entities[i]->id != a.id) resolveVerticalCollision(a, *entities[i]);
    }
}

void EntityManager::resolveHorizontalCollision(Entity& a, Entity&b) {
    if (!(a.x + a.width > b.x && a.x < b.x + b.width) || !(a.y + a.height > b.y && a.y < b.y + b.height)) {
        return;
    }
    if (a.vx > 0) {
        a.x = b.x - a.width;
        a.vx = 0;
    } else if (a.vx < 0) {
        a.x = b.x + b.width;
        a.vx = 0;
    }
}

void EntityManager::resolveHorizontalCollisions(Entity& a) {
    for (int i = 0; i < entities.size(); i++) { 
        if (entities[i]->id != a.id) resolveHorizontalCollision(a, *entities[i]);
    }
}