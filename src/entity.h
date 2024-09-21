#ifndef ENTITY
#define ENTITY

#include <SDL2/SDL.h>

class Entity {
    public:
        int id;
        float x, y;
        float vx, vy;
        float ax, ay;
        float width, height;
        bool grounded;
        SDL_Texture* renderable;
        
        void setVelocity(float newVx, float newVy);
        void setAcceleration(float newAx, float newAy);
        void updateX(float deltaTime);
        void updateY(float deltaTime);
        void applyGravity(float gravity, float deltaTime);
        void jump(float jumpStrength);

        Entity(float w, float h);
};

#endif