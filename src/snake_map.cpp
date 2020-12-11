#include "constants.hpp"
#include "snake_map.hpp"
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <cstdlib>

SnakeMap::SnakeMap(Snake* snake, Food* food) {
	this->snake_ = snake;
	this->food_ = food;
	this->types_ = new const char*[this->num_types_];
	this->types_[this->border_type_] = this->border_char_;
	this->types_[this->blank_type_] = this->blank_char_;
	this->types_[this->food_type_] = this->food_char_;
	this->types_[this->snake_type_] = this->snake_char_;

	for (unsigned y = 0; y != constants::map_height; ++y) {
		for (unsigned x = 0; x != constants::map_width; ++x) {
			if (x == 0 || x == constants::map_width - 1 || y == 0 || y == constants::map_height - 1) {
				this->map_array_[y][x] = this->border_type_;
			}
			else {
				this->map_array_[y][x] = this->blank_type_;
			}
		}
	}
}

void SnakeMap::draw() {
	for (unsigned y = 0; y != constants::map_height; ++y) {
		for (unsigned x = 0; x != constants::map_width; ++x) {
			mvprintw(y, x, this->types_[this->map_array_[y][x]]);
		}
	}
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
	return !(x == 0 || x == constants::map_width - 1 || y == 0 || y == constants::map_height - 1 || this->snake_->is_in_snake(y, x));
}