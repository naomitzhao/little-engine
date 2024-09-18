#include <iostream>
#include <SDL2/SDL.h>
#include "componentManager.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
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

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (!loadedSurface) {
        std::cout << "Couldn't load image" << path << ". SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
    if (!optimizedSurface) {
        std::cout << "Couldn't optimize surface. SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
}

void close() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

enum Directions {
    DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT,
};

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cout << "failed to init!" << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event e; 
    bool quit = false; 
    const int speed = 3;
    Component entity = Component();
    entity.renderable = SDL_CreateTexture(renderer, -1, 0, 20, 20);
    bool currInputs[4] = {false, false, false, false};

    while (quit == false){ 
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) {
                quit = true;
                continue;
            }

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);

            const Uint8* keyStates = SDL_GetKeyboardState( NULL );
            if (keyStates[SDL_SCANCODE_UP]) {
                // std::cout << "up ";
                currInputs[DIR_UP] = true;
            } else {
                currInputs[DIR_UP] = false;
            }
            if (keyStates[SDL_SCANCODE_DOWN]) {
                // std::cout << "down ";
                currInputs[DIR_DOWN] = true;
            } else {
                currInputs[DIR_DOWN] = false;
            }
            if (keyStates[SDL_SCANCODE_LEFT]) {
                // std::cout << "left ";
                currInputs[DIR_LEFT] = true;
            } else {
                currInputs[DIR_LEFT] = false;
            }
            if (keyStates[SDL_SCANCODE_RIGHT]) {
                // std::cout << "right ";
                currInputs[DIR_RIGHT] = true;
            } else {
                currInputs[DIR_RIGHT] = false;
            }

            bool keyless = true;
            for (bool input: currInputs) {
                if (input) keyless = false;
            }

            if (keyless) {
                // std::cout << "none";
                entity.resetVelocityAcceleration();
            } else {
                Coords velocity;
                if (currInputs[DIR_UP] && !currInputs[DIR_DOWN]) {
                    velocity.y = -speed;
                } else if (currInputs[DIR_DOWN] && !currInputs[DIR_UP]) {
                    velocity.y = speed;
                } else {
                    velocity.y = 0;
                }
                if (currInputs[DIR_LEFT] && !currInputs[DIR_RIGHT]) {
                    velocity.x = -speed;
                } else if (currInputs[DIR_RIGHT] && !currInputs[DIR_LEFT]) {
                    velocity.x = speed;
                } else {
                    velocity.x = 0;
                }
                // entity.setAcceleration(acceleration.x, acceleration.y);
                entity.updateVelocity(velocity.x, velocity.y);
                entity.updatePosition();
            }

            // std::cout << std::endl;

            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_Rect entityRect = { entity.position.x, entity.position.y, 20, 20 };
            SDL_RenderFillRect(renderer, &entityRect);

            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        } 
    }
    close();
    return EXIT_SUCCESS;
}