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
        void handleTopCollision(Entity& a, Entity& b);
        void handleLeftCollision(Entity& a, Entity& b);
        void handleRightCollision(Entity& a, Entity& b);
        void handleGroundCollisions(Entity& a);
        void handleTopCollisions(Entity& a);
        void handleLeftCollisions(Entity& a);
        void handleRightCollisions(Entity& a);
        bool isGroundCollision(Entity& a, Entity& b);
        bool isTopCollision(Entity& a, Entity& b);
        bool isLeftCollision(Entity& a, Entity& b);
        bool isRightCollision(Entity& a, Entity& b);
        Entity* findGroundCollision(Entity& a);
        Entity* findTopCollision(Entity& a);
        Entity* findLeftCollision(Entity& a);
        Entity* findRightCollision(Entity& a);
        void setGrounded(Entity& a);
};

#endif