#include "snake.hpp"
#include <ncurses.h>
#include <random>

Snake::Snake() {
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


bool Snake::is_in_snake(unsigned y, unsigned x) {
	std::pair<unsigned, unsigned> given_coords = std::make_pair(y, x);
	for (unsigned i = 0; i != this->snake_pos_.size(); ++i) {
		if (given_coords == this->snake_pos_[i]) {
			return true;
		}
	}

	return false;
}