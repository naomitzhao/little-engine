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
    a.y = b.y - a.height;
    a.vy = 0;
}

void EntityManager::handleTopCollision(Entity& a, Entity& b) {
    a.y = b.y + b.height;
    a.vy = 0;
}

// a collides into b's left side
void EntityManager::handleLeftCollision(Entity& a, Entity& b) {
    a.x = b.x - a.width;
    a.vx = 0;
}

// a collides into b's right side
void EntityManager::handleRightCollision(Entity& a, Entity& b) {
    a.x = b.x + b.width;
    a.vx = 0;
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

void EntityManager::handleTopCollisions(Entity& a) {
    Entity* found = findTopCollision(a);
    if (found->id != a.id) {
        handleTopCollision(a, *found);
    } 
}

void EntityManager::handleLeftCollisions(Entity& a) {
    Entity* found = findLeftCollision(a);
    if (found->id != a.id) {
        handleLeftCollision(a, *found);
    } 
}

void EntityManager::handleRightCollisions(Entity& a) {
    Entity* found = findRightCollision(a);
    if (found->id != a.id) {
        handleRightCollision(a, *found);
    } 
}

bool EntityManager::isGroundCollision(Entity& a, Entity& b) {
    if (a.y + a.height >= b.y && (a.x < b.x + b.width && a.x + a.width > b.x) && a.y + a.height <= b.y + b.height && a.y < b.y) {
        return true;
    }
    return false;
}

bool EntityManager::isTopCollision(Entity& a, Entity& b) {
    if (a.y <= b.y + b.height && (a.x < b.x + b.width && a.x + a.width > b.x) && a.y >= b.y && a.y + a.height > b.y + b.height) {
        return true;
    }
    return false;
}

bool EntityManager::isLeftCollision(Entity& a, Entity& b) {
    if (a.x + a.width > b.x && (a.y < b.y + b.height && a.y + a.height > b.y) && a.x < b.x) {
        return true;
    }
    return false;
}

bool EntityManager::isRightCollision(Entity& a, Entity& b) {
    if (a.x < b.x + b.width && (a.y < b.y + b.height && a.y + a.height > b.y) && a.x + a.width > b.x + b.width) {
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

Entity* EntityManager::findTopCollision(Entity& a) {
    for (int i = 0; i < entities.size(); i++) { 
        if (entities[i]->id != a.id && isTopCollision(a, *entities[i])) {
            return entities[i];
        }
    }
    return &a;
}

Entity* EntityManager::findLeftCollision(Entity& a) {
    for (int i = 0; i < entities.size(); i++) { 
        if (entities[i]->id != a.id && isLeftCollision(a, *entities[i])) {
            return entities[i];
        }
    }
    return &a;
}

Entity* EntityManager::findRightCollision(Entity& a) {
    for (int i = 0; i < entities.size(); i++) { 
        if (entities[i]->id != a.id && isRightCollision(a, *entities[i])) {
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