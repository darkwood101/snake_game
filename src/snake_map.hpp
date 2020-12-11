#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "constants.hpp"

class SnakeMap {

private:
	const char* map_char_ = "o";

public:
	void draw();
};


#endif