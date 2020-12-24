/*
This file contains the declaration of all global variables and functions.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdlib>

namespace globals {
    static constexpr size_t unitLength = 20;        // The unit length of snake's movement, in pixels.
    static constexpr size_t mapWidth = 800;         // The width of the map in pixels.
    static constexpr size_t mapHeight = 640;        // The height of the map in pixels.
    // Enumeration containing game start and exit codes.
    // Used in Game class.
    enum gameStatus {
        gameStart,
        gameContinue,
        userExit,
        playerDead
    };

    void SDLError();                                // A function to print the SDL error and exit the program.
}

#endif