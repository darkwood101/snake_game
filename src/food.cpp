#include "food.hpp"
#include "constants.hpp"
#include <time.h>
#include <cstdlib>
#include <ncurses.h>



bool Food::is_food(unsigned y, unsigned x) {
	return std::make_pair(y, x) == this->food_pos_;
}


void Food::generate() {
	static bool first_generation = true;
	if (first_generation) {
		srand(time(NULL));
		first_generation = false;
	}

	unsigned food_y = 1 + (rand() % (constants::map_height - 1));
	unsigned food_x = 1 + (rand() % (constants::map_width - 1));
	this->food_pos_ = std::make_pair(food_y, food_x);
}

std::pair<unsigned, unsigned> Food::get_food_pos() {
	return this->food_pos_;
}

void Food::print() {
	unsigned y = this->food_pos_.first;
	unsigned x = this->food_pos_.second;

	mvprintw(y, x, this->food_char_);
	refresh();
}