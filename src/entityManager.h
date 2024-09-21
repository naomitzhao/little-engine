#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

#include <vector>
#include "entity.h"

class EntityManager {
    public:
        std::vector<Entity*> entities;
        
        Entity* createEntity(float width, float height);
        bool isGroundCollision(Entity& a, Entity& b);
        void setGrounded(Entity& a);
        void resolveVerticalCollision(Entity& a, Entity& b);
        void resolveVerticalCollisions(Entity& a);
        void resolveHorizontalCollision(Entity& a, Entity&b);
        void resolveHorizontalCollisions(Entity& a);
};

#endif