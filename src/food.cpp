#include "food.hpp"

#include <time.h>
#include <cstdlib>
#include <ncurses.h>



bool Food::is_food(unsigned y, unsigned x) {
	return std::make_pair(y, x) == food_pos_;
}


void Food::generate() {
	static bool first_generation = true;
	if (first_generation) {
		srand(time(NULL));
		first_generation = false;
	}

	unsigned food_y = 1 + (rand() % (20 - 1));
	unsigned food_x = 1 + (rand() % (50 - 1));
	food_pos_ = std::make_pair(food_y, food_x);
}

std::pair<unsigned, unsigned> Food::get_food_pos() {
	return food_pos_;
}
