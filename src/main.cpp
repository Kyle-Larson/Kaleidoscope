#include <stdio.h>
#include <SDL.h>
//#include <SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main() {
    printf("hello, world!\n");

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    int result = 0;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return 0;
}