#include "snake.hpp"
#include <ncurses.h>
#include <random>

Snake::Snake() {
	for (unsigned i = 0; i != this->init_length_; ++i) {
		snake_pos_.push_back(std::make_pair(this->init_y_, this->init_x_ + i));
	}
}

/*void Snake::draw() {
	for (unsigned i = 0; i != snake_pos_.size() - 1; ++i) {
		mvprintw(snake_pos_[i].first, snake_pos_[i].second, this->body_char_);
	}
	unsigned last_pos = snake_pos_.size() -1;
	mvprintw(snake_pos_[last_pos].first, snake_pos_[last_pos].second, this->head_char_);
	refresh();
}*/


bool Snake::is_in_snake(std::pair<unsigned, unsigned> coords) {
	for (unsigned i = 0; i != this->snake_pos_.size(); ++i) {
		if (coords == this->snake_pos_[i]) {
			return true;
		}
	}

	return false;
}


bool Snake::is_snake_head(std::pair<unsigned, unsigned> coords) {
	return coords == this->snake_pos_[this->snake_pos_.size() - 1];
}

void Snake::move() {

	unsigned head_y = this->snake_pos_[snake_pos_.size() - 1].first;
	unsigned head_x = this->snake_pos_[snake_pos_.size() - 1].second;

	this->direction_mutex.lock();
	switch (this->direction) {
		case up: {
			--head_y;
			break;
		}

		case down: {
			++head_y;
			break;
		}

		case left: {
			--head_x;
			break;
		}

		case right: {
			++head_x;
			break;
		}
	}

	std::pair<unsigned, unsigned> new_pair = std::make_pair(head_y, head_x);
	this->snake_pos_.push_back(new_pair);
	this->snake_pos_.erase(this->snake_pos_.begin());
	this->direction_mutex.unlock();
}

void Snake::set_direction(int dir) {
	if (dir + this->direction == 3) {
		return;
	}
	if (dir == up || dir == down || dir == left || dir == right) {
		this->direction = dir;
	}
}