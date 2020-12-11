#ifndef SNAKE_H
#define SNAKE_H

#include "constants.hpp"
#include <cstdlib>
#include <vector>
#include <utility>

class Snake {
private:
	std::vector<std::pair<unsigned, unsigned>> snake_pos_;
	const unsigned init_length_ = 4;
	const unsigned init_y_ = constants::map_height / 2;
	const unsigned init_x_ = (constants::map_width / 2) - (this->init_length_ / 2);
	const char* head_char_ = "o";
	const char* body_char_ = "x";

public:
	Snake();
	void draw();
	bool is_in_snake(unsigned y, unsigned x);
};

#endif