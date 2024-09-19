#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <vector>
#include "entity.h"

class EntityManager {
    public:
        std::vector<Entity> entities;
        bool isCollision(Entity& a, Entity& b);
        void handleGroundCollision(Entity& entity, int groundY);
};

#endif