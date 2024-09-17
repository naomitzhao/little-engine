#include <iostream>
#include <SDL2/SDL.h>

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

int main(int argc, char* argv[]) {
    if (!init()) {
        std::cout << "failed to init!" << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event e; 
    bool quit = false; 
    while (quit == false){ 
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) {
                quit = true;
                continue;
            }

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        } 
    }
    close();
    return EXIT_SUCCESS;
}