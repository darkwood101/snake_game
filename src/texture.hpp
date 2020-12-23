/*
This header file contains the declaration of the Texture class.
The purpose of the Texture class is to provide handle SDL drawing, while providing an easy
interface to the rest of the application.
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <utility>

class Texture {

private:
    SDL_Texture* texture_;                                      // The actual hardware texture.
    SDL_Renderer* renderer_;                                    // Pointer to the renderer.
    int width_;                                                 // Width of the texture.
    int height_;                                                // Height of the texture.

public:
    Texture(SDL_Renderer* renderer, int width, int height);     // Constructor.
    ~Texture();                                                 // Destructor.
    void render(std::pair<unsigned, unsigned> coords);          // Renders the texture on the screen.
    void loadFromFile(const char* path);                        // Loads the texture from the file.
};

#endif