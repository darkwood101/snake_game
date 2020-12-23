/*
This header file contains the declaration of the Text class.
*/

#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text {

private:
    SDL_Renderer* renderer_;            // Pointer to the renderer.
    TTF_Font* font_;                    // Pointer to the font.
    SDL_Color textColor_;               // Color for the text.
    SDL_Texture* texture_;              // Pointer to the actual hardware texture.
    SDL_Rect renderRect_;               // The rectangle used for rendering.

public:
    Text(SDL_Renderer* renderer);       // Constructor.
    ~Text();                            // Destructor.
    void render(int x, int y);          // Renders the texture on the screen.
    void update(const char* message);   // Updates the text to be the string pointed to by `message`.

};


#endif