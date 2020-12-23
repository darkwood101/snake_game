/*
This header file contains the declaration of the Border class.
This class serves only to render the borders on the screen.
The reason why there are two separate textures for vertical and horizontal borders is simplicity.
This way, when rendering, we only need to specify the position of the border, and there's no rotation or scaling involved.
*/

#ifndef BORDER_H
#define BORDER_H

#include "texture.hpp"

class Border {

private:
    Texture verticalBorder_;            // The texture for the vertical border.
    Texture horizontalBorder_;          // The texture for the horizontal border.

public:
    Border(SDL_Renderer* renderer);     // Constructor.
    void render();                      // Renders the borders on the screen.

};

#endif