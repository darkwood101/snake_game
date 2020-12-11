#include "constants.hpp"
#include "snake_map.hpp"
#include <ncurses.h>

void SnakeMap::initialize() {
	for (unsigned y = 0; y != constants::map_height; ++y) {
		for (unsigned x = 0; x != constants::map_width; ++x) {
			if (x == 0 || y == 0 || x == constants::map_width - 1 || y == constants::map_height -1) {
				this->map_array[y][x] = 'o';
			}
			else {
				this->map_array[y][x] = ' ';
			}
		}
	}
}

void SnakeMap::print() {
	for (unsigned y = 0; y != constants::map_height; ++y) {
		for (unsigned x = 0; x != constants::map_width; ++x) {
			printw("%c", this->map_array[y][x]);
		}
		printw("\n");
	}
}