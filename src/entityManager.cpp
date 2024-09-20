#include "entityManager.h"
#include <iostream>

Entity* EntityManager::createEntity(float width, float height) {
    Entity* newEntity = new Entity(width, height);
    newEntity->id = entities.size();
    entities.push_back(newEntity);
    return newEntity;
}

bool EntityManager::isCollision(Entity& a, Entity& b) {
    if (b.x < a.x + a.width) {
        return true;
    }
    if (a.x < b.x + b.width) {
        return true;
    }
    if (b.y < a.y + a.height) {
        return true;
    }
    if (a.y < b.y + b.height) {
        return true;
    }
    return false;
}

void EntityManager::handleGroundCollision(Entity& a, Entity& b) {
    if (a.y + a.height >= b.y) {
        a.y = b.y - a.height;
        a.vy = 0;
    } 
}

void EntityManager::handleGroundCollisions(Entity& a) {
    Entity* found = findGroundCollision(a);
    if (found->id != a.id) {
        handleGroundCollision(a, *found);
        a.grounded = true;
    } else {
        a.grounded = false;
    }
}

bool EntityManager::isGroundCollision(Entity& a, Entity& b) {
    if (a.y + a.height >= b.y && (a.x <= b.x + b.width && a.x + a.width >= b.x) && a.y <= b.y + b.height) {
        return true;
    }
    return false;
}

Entity* EntityManager::findGroundCollision(Entity& a) {
    for (int i = 0; i < entities.size(); i++) { 
        if (entities[i]->id != a.id && isGroundCollision(a, *entities[i])) {
            return entities[i];
        }
    }
    return &a;
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