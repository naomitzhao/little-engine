#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <vector>
#include "entity.h"

class EntityManager {
    public:
        std::vector<Entity*> entities;
        Entity* createEntity(float width, float height);
        bool isCollision(Entity& a, Entity& b);
        void handleGroundCollision(Entity& a, Entity& b);
        void handleGroundCollisions(Entity& a);
        bool isGroundCollision(Entity& a, Entity& b);
        void setGrounded(Entity& a);
};

#endif