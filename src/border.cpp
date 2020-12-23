#include "border.hpp"
#include "globals.hpp"


// Border::Border(renderer)
//      Initializes and loads the texture for vertical and horizontal borders.
//      The texture path is hardcoded.

Border::Border(SDL_Renderer* renderer) : verticalBorder_(renderer, globals::unitLength, globals::mapHeight),
                                         horizontalBorder_(renderer, globals::mapWidth, globals::unitLength) {
    verticalBorder_.loadFromFile("res/border.bmp");
    horizontalBorder_.loadFromFile("res/border.bmp");
}


// Border::render()
//      Renders the borders on the screen.
//      The positions are specified to match the edges of the screen.
//      Note that there is some overlapping between horizontal and vertical borders
//      in the corners. This is fine and doesn't matter.

void Border::render() {
    verticalBorder_.render(std::make_pair(0, 0));
    verticalBorder_.render(std::make_pair(0, globals::mapWidth - globals::unitLength));
    horizontalBorder_.render(std::make_pair(0, 0));
    horizontalBorder_.render(std::make_pair(globals::mapHeight - globals::unitLength, 0));
}