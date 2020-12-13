#ifndef SNAKE_H
#define SNAKE_H

#include <utility>
#include <queue>
#include <vector>

class Snake {

private:
    std::vector<std::pair<unsigned, unsigned>> snake_pos_;              // Stores coordinates of snake body in form (y, x).
    const unsigned init_length_ = 8;                                    // Initial length of the snake.
    unsigned init_y_;                                                   // Initial y coordinate of the snake tail.
    unsigned init_x_;                                                   // Initial x coordinate of the snake tail.
    int direction = right;                                              // Initial direction of the snake.
    std::queue<int> new_directions;
    std::pair<unsigned, unsigned> head_;                                // Stores coordinates of the head.
    std::pair<unsigned, unsigned> tail_;                                // Stores coordinates of the tail.

public:
    Snake();                                                            // Constructor.
    bool is_in_snake(std::pair<unsigned, unsigned> coords);             // Returns true if the cell at `coords` is part of the snake body.
    bool is_snake_head(std::pair<unsigned, unsigned> coords);           // Returns true if the cell at `coords` is the snake head.
    void advance();                                                        // Moves the snake.
    void set_direction(int dir);                                        // Changes snake direction.
    std::pair<unsigned, unsigned> get_head();                           // Returns the coordinates of the snake head.
    std::vector<std::pair<unsigned, unsigned>> get_snake_pos();
    void clear_tail();
    // Enumeration of different movement directions.
    static constexpr int up = 0;
    static constexpr int down = 3;
    static constexpr int left = 1;
    static constexpr int right = 2;
};

#endif