/*
This header file contains the declaration of the Food class. It stores the coordinates of the food
for the snake, and it has method that enables generating food at a new position.
*/

#ifndef FOOD_H
#define FOOD_H

#include "snake.hpp"
#include "texture.hpp"
#include <random>

class Food {

private:
    std::pair<unsigned, unsigned> foodPos_;         // Coordinates of the food.
    Texture food_;                                  // Texture for the food.
    std::random_device randomDevice_;               // Random device as a source of randomness.
    std::mt19937 generator_;                        // Random number generator.
    std::uniform_int_distribution<> distrX_;        // Uniform distribution for x coordinates.
    std::uniform_int_distribution<> distrY_;        // Uniform distribution for y coordinates.

public:
    Food(SDL_Renderer* renderer);                   // Constructor.
    void render();                                  // Renders the food on the screen.
    void generate(Snake* snake);                    // Randomly generates a new position for the food.
    std::pair<unsigned, unsigned> getFoodPos();     // Returns the position of the food.
};

#endif