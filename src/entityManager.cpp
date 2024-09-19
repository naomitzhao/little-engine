#include "entityManager.h"

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

void EntityManager::handleGroundCollision(Entity& entity, int groundY) {
    if (entity.y + entity.height >= groundY) {
        entity.y = groundY - entity.height;
        entity.vy = 0;
        entity.grounded = true;
    } else {
        entity.grounded = false;
    }
}
