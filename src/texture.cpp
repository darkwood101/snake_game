#include "texture.hpp"
#include "globals.hpp"


// Texture::Texture(renderer, width, height)
//      The renderer needs to be provided as an argument, because rendering itself
//      requires a renderer as an argument. The width and the height are not going to be changed in
//      this application, so they should also be provided to the constructor.

Texture::Texture(SDL_Renderer* renderer, int width, int height) {
    renderer_ = renderer;
    width_ = width;
    height_ = height;
    texture_ = nullptr;
}


// Texture::render(coords)
//      Renders the texture at `coords`.

void Texture::render(std::pair<unsigned, unsigned> coords) {
    int y = coords.first;
    int x = coords.second;
    SDL_Rect renderRect = {x, y, width_, height_};
    SDL_RenderCopy(renderer_, texture_, nullptr, &renderRect);
}


// Texture::loadFromFile(const char* path)
//      Load the texture from the file located at `path`.
//      Make sure that any previous texture is destroyed.

void Texture::loadFromFile(const char* path) {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }

    SDL_Surface* loadedSurface = SDL_LoadBMP(path);
    if (loadedSurface == nullptr) globals::SDLError();

    texture_ = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
    if (texture_ == nullptr) globals::SDLError();

    SDL_FreeSurface(loadedSurface);
}


// Texture::~Texture()
//      Destroy the surface (frees the memory).

Texture::~Texture() {
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
}