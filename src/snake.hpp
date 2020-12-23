/*
This header file contains the declaration of the class Snake. The attribute store information about the
position of each piece of the snake's body, as well as the current direction and the future directions
that were requested by the player.

The methods enable obtaining information about the positions of various parts of the snake's body,
as well as changing the direction of the snake.
*/

#ifndef SNAKE_H
#define SNAKE_H

#include "texture.hpp"
#include <deque>
#include <vector>

class Snake {

private:
    std::vector<std::pair<unsigned, unsigned>> snakePos_;       // Stores coordinates of snake body in form (y, x).
    const size_t initLength_ = 8;                               // Initial length of the snake.
    unsigned initY_;                                            // Initial y coordinate of the snake tail.
    unsigned initX_;                                            // Initial x coordinate of the snake tail.
    int direction = right;                                      // Initial direction of the snake.
    std::deque<int> newDirections_;                             // This stores all directions that were requested by the user.
    std::pair<unsigned, unsigned> head_;                        // Stores coordinates of the head.
    std::pair<unsigned, unsigned> tail_;                        // Stores coordinates of the tail.
    Texture snakeHead_;                                         // Texture for the snake head.
    Texture snakeBody_;                                         // Texture for the snake body.

public:
    Snake(SDL_Renderer* renderer);                              // Constructor.
    bool isInSnake(std::pair<unsigned, unsigned> coords);       // Returns true if the cell at `coords` is part of the snake body.
    void advance();                                             // Moves the snake.
    void setDirection(int dir);                                 // Changes snake direction.
    int getLatestDirection();                                   // Returns the latest direction requested by the user.
    void render();                                              // Renders the snake.
    std::pair<unsigned, unsigned> getHead();                    // Returns the coordinates of the snake head.
    std::pair<unsigned, unsigned> getTail();                    // Returns the coordinates of the snake tail.
    void clearTail();                                           // Erase the tail from the vector of snake positions.
    // Enumeration of different movement directions.
    enum Direction {
        up,
        down,
        left,
        right
    };
};

#endif