#ifndef SNAKE_H
#define SNAKE_H

#include "constants.hpp"
#include <cstdlib>
#include <vector>
#include <utility>
#include <mutex>

class Snake {
private:
	std::vector<std::pair<unsigned, unsigned>> snake_pos_;
	const unsigned init_length_ = 8;
	const unsigned init_y_ = constants::map_height / 2;
	const unsigned init_x_ = (constants::map_width / 2) - (this->init_length_ / 2);
	const char* head_char_ = "o";
	const char* body_char_ = "x";
	int direction = up;
	std::pair<unsigned, unsigned> head_;
	std::pair<unsigned, unsigned> tail_;

public:
	Snake();
	void draw();
	bool is_in_snake(std::pair<unsigned, unsigned> coords);
	bool is_snake_head(std::pair<unsigned, unsigned> coords);
	void move();
	void set_direction(int dir);	
	static constexpr int up = 0;
	static constexpr int down = 1;
	static constexpr int left = 2;
	static constexpr int right = 3;
	std::mutex direction_mutex;
};

#endif