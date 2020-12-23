/*
This file contains the definitions of all global functions.
*/

#include "globals.hpp"
#include <SDL2/SDL.h>

namespace globals {
    void SDLError() {
        fprintf(stderr, "SDL error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}