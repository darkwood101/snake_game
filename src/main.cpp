#include "globals.hpp"
#include "game.hpp"

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;
    Game game;
    if (game.startScreen() == globals::userExit) return 0;
    if (game.run() == globals::playerDead) game.gameOverScreen();
    return 0;
}