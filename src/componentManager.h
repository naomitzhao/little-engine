#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include <SDL2/SDL.h>
#include <vector>

class Entity {
    public:
        float x, y;
        float vx, vy;
        float ax, ay;
        int width, height;
        bool grounded;
        SDL_Texture* renderable;
        void setVelocity(int newVx, int newVy);
        void setAcceleration(int newAx, int newAy);
        void updatePosition(float deltaTime);
        void applyGravity(float gravity, float deltaTime);

        Entity(SDL_Texture* texture);
        Entity();
};

class EntityManager {
    public:
        std::vector<Entity> entities;
        
};

#endif