#include "globals.hpp"
#include "game.hpp"

int main() {
    Game game;
    if (game.startScreen() == globals::userExit) return 0;
    if (game.run() == globals::playerDead) game.gameOverScreen();
    return 0;
}