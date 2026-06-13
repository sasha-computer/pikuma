#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // TODO: Create a SDL window

    // TODO: Create a SDL renderer

    return true;
}

int main(void) {

    initialize_window();

    return 0;
}
