#include "snake.hpp"
#include <ncurses.h>
#include <random>

Snake::Snake() {
	for (unsigned i = 0; i != init_length_; ++i) {
		snake_pos_.push_back(std::make_pair(init_y_, init_x_ + i));
	}

	head_ = snake_pos_[snake_pos_.size() - 1];
	tail_ = snake_pos_[0];
}


bool Snake::is_in_snake(std::pair<unsigned, unsigned> coords) {
	for (unsigned i = 0; i != snake_pos_.size() - 1; ++i) {
		if (coords == snake_pos_[i]) {
			return true;
		}
	}

	return false;
}


bool Snake::is_snake_head(std::pair<unsigned, unsigned> coords) {
	return coords == snake_pos_[snake_pos_.size() - 1];
}

void Snake::move(bool grow) {

	unsigned head_y = snake_pos_[snake_pos_.size() - 1].first;
	unsigned head_x = snake_pos_[snake_pos_.size() - 1].second;

	direction_mutex.lock();
	switch (direction) {
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
	head_ = new_pair;
	snake_pos_.push_back(new_pair);
	if (!grow) {
		snake_pos_.erase(snake_pos_.begin());
	}
	tail_ = snake_pos_[0];
	direction_mutex.unlock();
}

void Snake::set_direction(int dir) {
	if (dir + direction == 3) {
		return;
	}
	if (dir == up || dir == down || dir == left || dir == right) {
		direction = dir;
	}
}


std::pair<unsigned, unsigned> Snake::get_head() {
	return snake_pos_[snake_pos_.size() - 1];
}