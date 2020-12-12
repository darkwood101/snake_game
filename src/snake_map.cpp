#include "constants.hpp"
#include "snake_map.hpp"
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <thread>

SnakeMap::SnakeMap(Snake* snake, Food* food) {
	this->snake_ = snake;
	this->food_ = food;
	this->game_over = false;
}

void SnakeMap::draw() {
	for (unsigned y = 0; y != constants::map_height; ++y) {
		for (unsigned x = 0; x != constants::map_width; ++x) {
			std::pair<unsigned, unsigned> coords = std::make_pair(y, x);
			if (this->snake_->is_snake_head(coords)) {
				mvprintw(y, x, this->snake_head_);
			}
			else if (this->snake_->is_in_snake(coords)) {
					mvprintw(y, x, this->snake_char_);
			}
			else if (coords == this->food_->get_food_pos()) {
				mvprintw(y, x, this->food_char_);
			}
			else if (x == 0 || x == constants::map_width - 1 || y == 0 || y == constants::map_height - 1) {
				mvprintw(y, x, this->border_char_);
			}
			else {
				mvprintw(y, x, this->blank_char_);
			}
		}
	}

	refresh();
}

/*void SnakeMap::set(unsigned y, unsigned x, const char* type) {
	this->map_array_[y][x] = (char*) type;
}*/


void SnakeMap::generate_food() {
	std::pair<unsigned, unsigned> current_food_pos = this->food_->get_food_pos();
	unsigned y = current_food_pos.first;
	unsigned x = current_food_pos.second;
	mvprintw(y, x, this->blank_char_);
	do {
		this->food_->generate();
	}
	while (!(this->is_blank(this->food_->get_food_pos())));

}


bool SnakeMap::is_blank(std::pair<unsigned, unsigned> coords) {
	unsigned y = coords.first;
	unsigned x = coords.second;
	return !((x == 0) || (x == constants::map_width - 1) || (y == 0) || (y == constants::map_height - 1) || (this->snake_->is_in_snake(coords)));
}

//threading
void SnakeMap::input_thread() {
	
	while (true) {
		char ch = getch();
		if (this->game_over) {
			endwin();
			exit(0);
		}
		this->snake_->direction_mutex.lock();
		switch(ch) {
			case 'w': {
				this->snake_->set_direction(this->snake_->up);
				break;
			}
			case 's': {
				this->snake_->set_direction(this->snake_->down);
				break;
			}
			case 'a': {
				this->snake_->set_direction(this->snake_->left);
				break;
			}
			case 'd': {
				this->snake_->set_direction(this->snake_->right);
			}
		}

		this->snake_->direction_mutex.unlock();
	}
}

void SnakeMap::wait_input() {
	std::thread th(&SnakeMap::input_thread, this);
	th.detach();
}

int SnakeMap::move_snake() {
	this->snake_->move();
	if (this->is_dead()) {
		this->game_over = true;
		return -1;
	}
	this->draw();
	return 0;
}

bool SnakeMap::is_dead() {
	return !(this->is_blank(this->snake_->get_head()));
}