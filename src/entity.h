#ifndef ENTITY
#define ENTITY

#include <SDL2/SDL.h>

class Entity {
    public:
        float x, y;
        float vx, vy;
        float ax, ay;
        int width, height;
        bool grounded;
        SDL_Texture* renderable;
        void setVelocity(float newVx, float newVy);
        void setAcceleration(float newAx, float newAy);
        void updatePosition(float deltaTime);
        void applyGravity(float gravity, float deltaTime);
        void jump(float jumpStrength);

        Entity(int w, int h);
};

#endif