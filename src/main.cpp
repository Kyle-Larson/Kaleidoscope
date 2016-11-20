#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window* window;
SDL_Renderer* renderer;

void loop() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect rect = { 0, 0, 100, 50 };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

int main() {
    printf("hello, world!\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR: %s\n", SDL_GetError());
        return 1;
    }

    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    if (renderer == 0) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(loop, 60, 1);
#else
    while (true) {
        loop();
    }
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}