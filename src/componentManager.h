#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include <SDL2/SDL.h>
#include <vector>

struct Position {
    int x, y;
};

struct Velocity {
    int x, y;
};

class Component {
    public:
        Position position;
        Velocity velocity;
        SDL_Texture* renderable;
        int terminalVelocity;
        void updateVelocity(int dvx, int dvy);
        void updatePosition();

        Component(SDL_Texture* texture);
        Component();
};

class ComponentManager {
    public:
        std::vector<Component> components;
        
};

#endif