#include "constants.hpp"
#include "snake_map.hpp"
#include <ncurses.h>


void SnakeMap::draw() {
	for (unsigned y = 0; y < constants::map_height; ++y) {
		for (unsigned x = 0; x < constants::map_width; x += constants::map_width - 1) {
			mvprintw(y, x, this->map_char_);
		}
	}

	for (unsigned y = 0; y < constants::map_height; y += constants::map_height - 1) {
		for (unsigned x = 1; x < constants::map_width - 1; ++x) {
			mvprintw(y, x, this->map_char_);
		}
	}
}