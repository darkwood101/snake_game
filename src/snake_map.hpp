#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "constants.hpp"
#include "snake.hpp"
#include "food.hpp"
#include <utility>

class SnakeMap {

private:
	Snake* snake_;
	Food* food_;
	const char* border_char_ = "o";
	const char* blank_char_ = " ";
	const char* food_char_ = "$";
	const char* snake_char_ = "x";
	const char* snake_head_ = "o";
	int border_type_ = 0;
	int blank_type_ = 1;
	int food_type_ = 2;
	int snake_type_ = 3;
	int snake_head_type_ = 4;
	int num_types_ = 5;
	const char** types_;
	int map_array_[constants::map_height][constants::map_width];
	bool first_generation_ = true;
	std::pair<unsigned, unsigned> food_pos_;

public:
	SnakeMap(Snake* snake, Food* food);
	void draw();
	void set(unsigned y, unsigned x, const char* type);
	void generate_food();
	bool is_blank(std::pair<unsigned, unsigned> coords);
	void input_thread();
	void wait_input();
	void move_snake();
};


#endif