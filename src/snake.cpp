#include "snake.hpp"
#include "game.hpp"
#include "os_dependent.hpp"
#include <ncurses.h>
#include <random>


// Snake::Snake()
//      Initializes the inital snake positions so the snake is at the center of the screen.
//      Pushes initial snake head and body coordinates into the positions vectors.
//      Initializes head_ and tail_

Snake::Snake() {
    init_x_ = Game::map_width / 2 - (init_length_ / 2);
    init_y_ = Game::map_height / 2;

    for (unsigned i = 0; i != init_length_; ++i) {
        snake_pos_.push_back(std::make_pair(init_y_, init_x_ + i));
    }

    head_ = snake_pos_[snake_pos_.size() - 1];
    tail_ = snake_pos_[0];
}


// Snake::is_in_snake(coords)
//      Returns true if any part of the snake body, except the head, is located at
//      `coords`.

bool Snake::is_in_snake(std::pair<unsigned, unsigned> coords) {
    for (unsigned i = 0; i != snake_pos_.size() - 1; ++i) {
        if (coords == snake_pos_[i]) {
            return true;
        }
    }

    return false;
}


// Snake::move(grow)
//      Performs the movement of the snake. Depending on the direction,
//      positions of the head are changed and are pushed into the positions vector.

void Snake::advance() {
    unsigned head_y = snake_pos_[snake_pos_.size() - 1].first;
    unsigned head_x = snake_pos_[snake_pos_.size() - 1].second;

    if (new_directions_.size() > 0) {
        direction = new_directions_.front();
        new_directions_.pop_front();
    }

    switch (direction) {
        case up:
            --head_y;
            break;

        case down:
            ++head_y;
            break;

        case left:
            --head_x;
            break;

        case right:
            ++head_x;
            break;
    }

    std::pair<unsigned, unsigned> new_pair = std::make_pair(head_y, head_x);
    head_ = new_pair;
    snake_pos_.push_back(new_pair);
}


// Snake::set_direction(int dir)
//      Pushes `dir` into the deque `new_directions_`, which contains
//      all directions requested by the user that will eventually be executed.
//      If `dir` is the same as the latest direction requested by the user, nothing happens.
//      This is to prevent locking the snake going in one direction -- if the user presses and holds
//      down a key, Game::process_input will send requests much faster than the game delay is.
//      Then, the snake will stop being responsive until all directions are exhausted, which usually
//      causes the snake to die. This prevents that from happening. Some abuses are still possible,
//      where the player rapidly and continuously presses two different keys, which will cause the snake
//      to move on a zig-zag trajectory, but that is okay and is less problematic than the previously
//      described problem.

void Snake::set_direction(int dir) {
    if (dir != get_latest_direction()) {
        new_directions_.push_back(dir);
    }
}


// Snake::get_latest_direction()
//      Returns the direction that was most recently requested by the user. If the `new_directions_` deque is empty,
//      returns the current direction.

int Snake::get_latest_direction() {
    if (new_directions_.empty()) {
        return direction;
    }
    else {
        return new_directions_.back();
    }
}


// Snake::get_head()
//      Returns the coordinates of the snake head.

std::pair<unsigned, unsigned> Snake::get_head() {
    return head_;
}


// Snake::get_tail()
//      Returns the coordinates of the snake tail.

std::pair<unsigned, unsigned> Snake::get_tail() {
    return tail_;
}


// Snake::get_snake_pos()
//      Returns the vector of positions of snake body.

std::vector<std::pair<unsigned, unsigned>> Snake::get_snake_pos() {
    return snake_pos_;
}


// Snake::clear_tail()
//      Erases the snake tail from the vector, and draws a blank char on the board.
//      Updates the tail_ attribute.

void Snake::clear_tail(char blank_char) {
    os::draw_char(snake_pos_[0], blank_char);
    snake_pos_.erase(snake_pos_.begin());
    tail_ = snake_pos_[0];
}