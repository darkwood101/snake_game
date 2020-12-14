/*
This header file contains the declaration of the Food class. It stores the coordinates of the food
for the snake, and it has method that enable obtaining those coordinates, as well as generating new ones.
*/

#ifndef FOOD_H
#define FOOD_H

#include <utility>

class Food {

private:
    std::pair<unsigned, unsigned> food_pos_;        // Coordinates of the food.

public:
    std::pair<unsigned, unsigned> get_food_pos();   // Returns the coordinates of the food.
    void generate();                                // Randomly generates a new position for the food.
};

#endif