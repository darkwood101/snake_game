#include "food.hpp"
#include "game.hpp"

#include <time.h>
#include <cstdlib>
#include <ncurses.h>


// Food::generate()
//		Generate a new random position for the food.
//		This function doesn't check whether the position is OK.
//		The check is performed by Game::move_snake().

void Food::generate() {
	static bool first_generation = true;
	if (first_generation) {
		srand(time(NULL));
		first_generation = false;
	}

	unsigned food_y = 1 + (rand() % (Game::map_height - 1));
	unsigned food_x = 1 + (rand() % (Game::map_width - 1));
	food_pos_ = std::make_pair(food_y, food_x);
}


// Food::get_food_pos()
//		Returns the current position of the food.

std::pair<unsigned, unsigned> Food::get_food_pos() {
	return food_pos_;
}
