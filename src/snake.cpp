#include "snake.hpp"
#include <ncurses.h>

void Snake::initialize() {
	for (unsigned i = 0; i != this->init_length_; ++i) {
		snake_pos_.push_back(std::make_pair(this->init_y_, this->init_x_ + i));
	}
}

void Snake::draw() {
	for (unsigned i = 0; i != snake_pos_.size() - 1; ++i) {
		mvprintw(snake_pos_[i].first, snake_pos_[i].second, this->body_char_);
	}
	unsigned last_pos = snake_pos_.size() -1;
	mvprintw(snake_pos_[last_pos].first, snake_pos_[last_pos].second, this->head_char_);
}

