#include "snake.hpp"
#include "game.hpp"
#include "globals.hpp"


// Snake::Snake()
//      Initializes the inital snake positions so the snake is at the center of the screen.
//      Pushes initial snake head and body coordinates into the positions vectors.
//      Initializes head_ and tail_.
//      Initializes and loads the textures for the head and the body from the corresponding .bmp files. These paths
//      are hardcoded here.

Snake::Snake(SDL_Renderer* renderer) : snakeHead_(renderer, globals::unitLength, globals::unitLength), snakeBody_(renderer, globals::unitLength, globals::unitLength) {
    snakeHead_.loadFromFile("res/snakeHead.bmp");
    snakeBody_.loadFromFile("res/snakeBody.bmp");

    initX_ = globals::mapWidth / 2 - ((initLength_ / 2) * globals::unitLength);
    initY_ = globals::mapHeight / 2;

    for (unsigned i = 0; i != initLength_; ++i) {
        snakePos_.push_back(std::make_pair(initY_, initX_ + (i * globals::unitLength)));
    }

    head_ = snakePos_[snakePos_.size() - 1];
    tail_ = snakePos_[0];
}


// Snake::isInSnake(coords)
//      Returns true if any part of the snake body, except the head, is located at
//      `coords`.

bool Snake::isInSnake(std::pair<unsigned, unsigned> coords) {
    for (unsigned i = 0; i != snakePos_.size() - 1; ++i) {
        if (coords == snakePos_[i]) {
            return true;
        }
    }

    return false;
}


// Snake::move(grow)
//      Performs the movement of the snake. Depending on the direction,
//      positions of the head are changed and are pushed into the positions vector.

void Snake::advance() {
    unsigned head_y = snakePos_[snakePos_.size() - 1].first;
    unsigned head_x = snakePos_[snakePos_.size() - 1].second;

    if (newDirections_.size() > 0) {
        direction = newDirections_.front();
        newDirections_.pop_front();
    }

    switch (direction) {
        case up:
            head_y -= globals::unitLength;
            break;

        case down:
            head_y += globals::unitLength;
            break;

        case left:
            head_x -= globals::unitLength;
            break;

        case right:
            head_x += globals::unitLength;
            break;
    }

    std::pair<unsigned, unsigned> new_pair = std::make_pair(head_y, head_x);
    head_ = new_pair;
    snakePos_.push_back(new_pair);
}


// Snake::set_direction(int dir)
//      Pushes `dir` into the deque `newDirections_`, which contains
//      all directions requested by the user that will eventually be executed.
//      If `dir` is the same as the latest direction requested by the user, nothing happens.
//      This is to prevent locking the snake going in one direction -- if the user presses and holds
//      down a key, Game::processInput will send requests much faster than the game delay is.
//      Then, the snake will stop being responsive until all directions are exhausted, which usually
//      causes the snake to die. This prevents that from happening.

void Snake::setDirection(int dir) {
    if (dir != getLatestDirection()) {
        newDirections_.push_back(dir);
    }
}


// Snake::getLatestDirection()
//      Returns the direction that was most recently requested by the user. If the `newDirections_` deque is empty,
//      returns the current direction.

int Snake::getLatestDirection() {
    if (newDirections_.empty()) {
        return direction;
    }
    else {
        return newDirections_.back();
    }
}


// Snake::getHead()
//      Returns the coordinates of the snake head.

std::pair<unsigned, unsigned> Snake::getHead() {
    return head_;
}


// Snake::getTail()
//      Returns the coordinates of the snake tail.

std::pair<unsigned, unsigned> Snake::getTail() {
    return tail_;
}


// Snake::clearTail()
//      Erases the snake tail from the vector.
//      Updates the tail_ attribute.

void Snake::clearTail() {
    snakePos_.erase(snakePos_.begin());
    tail_ = snakePos_[0];
}


// Snake::render()
//      Renders the snake on the screen. This is done by
//      calling render with the positions given by
//      the snake positions from snakePos_.

void Snake::render() {
    for (size_t i = 0; i != snakePos_.size() - 1; ++i) {
        snakeBody_.render(snakePos_[i]);
    }

    snakeHead_.render(snakePos_[snakePos_.size() - 1]);
}