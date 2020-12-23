#include "text.hpp"
#include "globals.hpp"


// Text::Text(renderer)
//      The renderer needs to be provided as an argument, because rendering itself
//      requires a renderer as an argument.
//      Loads the font (the path is hardcoded).
//      Sets the text color to white, and initializes the rendering rectangle and the texture pointer.

Text::Text(SDL_Renderer* renderer) {
    renderer_ = renderer;
    font_ = TTF_OpenFont("res/font/RobotoMono-Medium.ttf", 28);
    if (font_ == nullptr) globals::SDLError();
    textColor_ = {255, 255, 255, 255};
    renderRect_ = {0, 0, 0, 0};
    texture_ = nullptr;
}


// Text::render(x, y)
//      Renders the texture at coordinates (y, x).
//      (With the current code layout, y always comes first. That's here since ncurses and v1.0, and it might get changed.)

void Text::render(int x, int y) {
    renderRect_.x = x;
    renderRect_.y = y;
    SDL_RenderCopy(renderer_, texture_, nullptr, &renderRect_);
}


// Text::update(message)
//      Updates the texture to show the string pointed to by `message`.
//      Makes sure to free the previous texture.

void Text::update(const char* message) {
    if (texture_ != nullptr) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }

    TTF_SizeText(font_, message, &renderRect_.w, &renderRect_.h);
    SDL_Surface* surface = TTF_RenderText_Solid(font_, message, textColor_);
    texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);
}


// Text::~Text()
//      Closes the font and destroys the texture.

Text::~Text() {
    if (font_ != nullptr) TTF_CloseFont(font_);
    if (texture_ != nullptr) SDL_DestroyTexture(texture_);
}