#ifndef SNAKE_MAP_H
#define SNAKE_MAP_H

#include "constants.hpp"
#include "snake.hpp"
#include "food.hpp"
#include <utility>
#include <atomic>

class SnakeMap {

private:
	Snake* snake_;
	Food* food_;
	const char* border_char_ = "o";
	const char* blank_char_ = " ";
	const char* food_char_ = "$";
	const char* snake_char_ = "x";
	const char* snake_head_ = "o";
	std::atomic<bool> game_over;

public:
	SnakeMap(Snake* snake, Food* food);
	void draw();
	void set(unsigned y, unsigned x, const char* type);
	void generate_food();
	bool is_blank(std::pair<unsigned, unsigned> coords);
	void input_thread();
	void wait_input();
	int move_snake();
	bool is_dead();
	bool ate_food();
};


#endif