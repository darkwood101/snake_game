/*
This header file contains the declaration of the class Snake. The attribute store information about the
position of each piece of the snake's body, as well as the current direction and the future directions
that were requested by the player.

The methods enable obtaining information about the positions of various parts of the snake's body,
as well as changing the direction of the snake.
*/

#ifndef SNAKE_H
#define SNAKE_H

#include <utility>
#include <deque>
#include <vector>

class Snake {

private:
    std::vector<std::pair<unsigned, unsigned>> snake_pos_;              // Stores coordinates of snake body in form (y, x).
    const unsigned init_length_ = 8;                                    // Initial length of the snake.
    unsigned init_y_;                                                   // Initial y coordinate of the snake tail.
    unsigned init_x_;                                                   // Initial x coordinate of the snake tail.
    int direction = right;                                              // Initial direction of the snake.
    std::deque<int> new_directions_;                                     // This stores all directions that were requested by the user.
    std::pair<unsigned, unsigned> head_;                                // Stores coordinates of the head.
    std::pair<unsigned, unsigned> tail_;                                // Stores coordinates of the tail.

public:
    Snake();                                                            // Constructor.
    bool is_in_snake(std::pair<unsigned, unsigned> coords);             // Returns true if the cell at `coords` is part of the snake body.
    void advance();                                                     // Moves the snake.
    void set_direction(int dir);                                        // Changes snake direction.
    int get_latest_direction();                                         // Returns the latest direction requested by the user.
    std::pair<unsigned, unsigned> get_head();                           // Returns the coordinates of the snake head.
    std::pair<unsigned, unsigned> get_tail();                           // Get the coordinates of the tail.
    std::vector<std::pair<unsigned, unsigned>> get_snake_pos();         // Return the vector of snake positions.
    void clear_tail(char blank_char);                                   // Erase the tail from the vector of snake positions and clear it from the screen.
    // Enumeration of different movement directions.
    static constexpr int up = 0;
    static constexpr int down = 3;
    static constexpr int left = 1;
    static constexpr int right = 2;
};

#endif