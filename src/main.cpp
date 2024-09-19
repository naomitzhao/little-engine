#include <iostream>
#include <SDL2/SDL.h>
#include "componentManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init();
void close();

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Couldn't initialize SDL. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("engine :D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Couldn't make window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Couldn't make RENDERER. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cout << "failed to init!" << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event e; 
    bool quit = false; 
    const int speed = 200;
    const float timeStep = 0.016f;
    Entity entity = Entity();
    entity.renderable = SDL_CreateTexture(renderer, -1, 0, 20, 20);

    Uint32 lastFrameTime = SDL_GetTicks();

    while (!quit){ 
        Uint32 currFrameTime = SDL_GetTicks();
        float deltaTime = (currFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currFrameTime;

        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }}

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        float vx = 0.0;
        float vy = 0.0;
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            vy = -speed;
        } else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            vy = speed;
        } 

        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            vx = -speed;
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            vx = speed;
        } 

        entity.setVelocity(vx, vy);
        entity.updatePosition(deltaTime);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect entityRect = { entity.x, entity.y, 20, 20 };
        SDL_RenderFillRect(renderer, &entityRect);

        SDL_RenderPresent(renderer);
        
        Uint32 frameTime = SDL_GetTicks() - currFrameTime;
        if (frameTime < timeStep * 1000.0f) {
            SDL_Delay((timeStep * 1000.0f) - frameTime);
        }
    }
    close();
    return EXIT_SUCCESS;
}