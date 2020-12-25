#include "food.hpp"
#include "globals.hpp"


// Food::Food(renderer)
//      Initializes the food texture and loads the .bmp file for the texture.
//      The path to the file is hardcoded.
//      Initializes the distributions. The distributions are initialized in such a way to ensure
//      that the food will not be generated past the borders of the screen.

Food::Food(SDL_Renderer* renderer) : food_(renderer, globals::unitLength, globals::unitLength), generator_(randomDevice_()),
                                     distrX_(1, (globals::mapWidth / globals::unitLength) - 2),
                                     distrY_(1, (globals::mapHeight / globals::unitLength) - 2) {
    food_.loadFromFile("res/food.bmp");
}


// Food::generate()
//      Generate a new random position for the food.
//      Repeats generation until the food position doesn't collide with the position
//      of the snake. This is why it takes a pointer to snake, in order to have access to snake's positions.

void Food::generate(Snake* snake) {
    do {
        foodPos_ = std::make_pair(distrY_(generator_) * globals::unitLength, distrX_(generator_) * globals::unitLength);
    }
    while ((snake->isInSnake(foodPos_)) || (foodPos_ == snake->getHead()));
}


// Food::getFoodPos()
//      Returns the current position of the food.

std::pair<unsigned, unsigned> Food::getFoodPos() {
    return foodPos_;
}


// Food::render()
//      Renders the food on the screen.

void Food::render() {
    food_.render(foodPos_);
}
