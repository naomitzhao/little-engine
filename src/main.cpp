#include <iostream>
#include <SDL2/SDL.h>
#include "entityManager.h"
#include "entity.h"

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
    EntityManager entityManager = EntityManager();

    Entity* player = entityManager.createEntity(20.0, 20.0); // 0
    Entity* ground = entityManager.createEntity(float(SCREEN_WIDTH), 40.0); // 1
    Entity* leftWall = entityManager.createEntity(0.0, float(SCREEN_HEIGHT)); // 2
    Entity* rightWall = entityManager.createEntity(0.0, float(SCREEN_HEIGHT)); // 3
    Entity* obstacle = entityManager.createEntity(100, 20);

    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;
    ground->x = 0;
    ground->y = SCREEN_HEIGHT - ground->height;
    rightWall->x = float(SCREEN_WIDTH);
    obstacle->x = 400;
    obstacle->y = 350;

    player->renderable = SDL_CreateTexture(renderer, -1, 0, player->width, player->height);
    ground->renderable = SDL_CreateTexture(renderer, -1, 0, ground->width, ground->height);

    Uint32 lastFrameTime = SDL_GetTicks();

    // std::cout << "ground: " << ground->x << " " << ground->y << " " << ground->width << " " << ground->height << std::endl;
    // std::cout << "player: " << player->x << " " << player->y << " " << player->width << " " << player->height << std::endl;

    while (!quit){ 
        Uint32 currFrameTime = SDL_GetTicks();
        float deltaTime = (currFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currFrameTime;

        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }}

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[SDL_SCANCODE_UP]) {
            player->jump(300.0);
        } 

        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            player->vx = -speed;
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            player->vx = speed;
        } else {
            player->vx = 0;
        }

        // std::cout << player->x << " " << player->y << std::endl;

        player->applyGravity(500.0, deltaTime);
        player->updatePosition(deltaTime);
        entityManager.handleGroundCollisions(*player);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect playerRect = { player->x, player->y, float(player->width), float(player->height) };
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect groundRect = { ground->x, ground->y, float(ground->width), float(ground->height) };
        SDL_RenderFillRect(renderer, &groundRect);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect obstacleRect = { obstacle->x, obstacle->y, obstacle->width, obstacle->height };
        SDL_RenderFillRect(renderer, &obstacleRect);

        SDL_RenderPresent(renderer);
        
        Uint32 frameTime = SDL_GetTicks() - currFrameTime;
        if (frameTime < timeStep * 1000.0f) {
            SDL_Delay((timeStep * 1000.0f) - frameTime);
        }
    }
    close();
    return EXIT_SUCCESS;
}