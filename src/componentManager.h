#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include <SDL2/SDL.h>
#include <vector>

struct Coords {
    int x, y;
};

class Component {
    public:
        Coords position;
        Coords velocity;
        Coords acceleration;
        SDL_Texture* renderable;
        int terminalVelocity;
        void updatePosition();
        void updateVelocity(int vx, int vy);
        void updateVelocity();
        void setAcceleration(int ax, int ay);
        void resetVelocityAcceleration();

        Component(SDL_Texture* texture);
        Component();
};

class ComponentManager {
    public:
        std::vector<Component> components;
        
};

#endif