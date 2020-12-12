#include "snake.hpp"
#include "game.hpp"
#include <ncurses.h>
#include <random>


// Snake::Snake()
//		Initializes the inital snake positions so the snake is at the center of the screen.
//		Pushes initial snake head and body coordinates into the positions vectors.
//		Initializes head_ and tail_

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
//		Returns true if any part of the snake body, except the head, is located at
//		`coords`.

bool Snake::is_in_snake(std::pair<unsigned, unsigned> coords) {
	for (unsigned i = 0; i != snake_pos_.size() - 1; ++i) {
		if (coords == snake_pos_[i]) {
			return true;
		}
	}

	return false;
}


// Snake::is_snake_head(coords)
//		Returns true if the snake head is located at `coords`.

bool Snake::is_snake_head(std::pair<unsigned, unsigned> coords) {
	return coords == snake_pos_[snake_pos_.size() - 1];
}


// Snake::move(grow)
//		Performs the movement of the snake. Depending on the direction,
//		positions of the head are changed and are pushed into the positions vector.
//		If grow is true, it means that the snake should grow one unit, so in that case
//		the tail is left alone. Otherwise, the tail is erased from the vector.
//		The access to direction is locked by the mutex, to avoid race conditions
//		with the thread that's listening to the user input.

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


// Snake::set_direction(int dir)
//		Changes the direction of the snake to `dir`.
//		If `dir` is the opposite of the current direction,
//		nothing happens. The condition `dir + direction == 3` is specific
//		and somewhat hardcoded. It will be true if and only if `dir` is the
//		opposite of the current direction.

void Snake::set_direction(int dir) {
	if (dir + direction == 3) {
		return;
	}
	if (dir == up || dir == down || dir == left || dir == right) {
		direction = dir;
	}
}


// Snake::get_head()
//		Returns the coordinates of the snake head.

std::pair<unsigned, unsigned> Snake::get_head() {
	return head_;
}