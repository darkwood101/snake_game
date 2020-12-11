#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "constants.hpp"

class SnakeMap {
	private:
		char map_array[constants::map_height][constants::map_width];

	public:
		void print();
		void initialize();
};


#endif